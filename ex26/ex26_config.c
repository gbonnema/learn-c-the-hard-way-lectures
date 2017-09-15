#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <glob.h>
#include "ex26_config.h"
#include "dbg.h"

const size_t max_log_fname = MAX_LOG_FNAME;
const size_t max_logfile_array = MAX_LOGFILE_ARRAY;

/* prototypes */
int glob_fname(char *log_fname, config_file_t *cfg_file);


config_t *read_config(const char *config_name)
{
    FILE *fd_config = NULL;

    config_t *config = calloc(1, sizeof(config_t));
    check(config, "Allocation of config struct failed");
    config->nlogfiles = 0;

    check(access(config_name, R_OK) == 0,
          "Config file %s does not exist or user has no read access", config_name);

    fd_config = fopen(config_name, "r");
    check(fd_config, "Configuration file %s would not open", config_name);

    size_t size = 255;
    char *pattern = calloc(size, sizeof(char));
    while(getline(&pattern, &size, fd_config) != -1)
    {
        /* process pattern */
        config_file_t *cfg_file = &config->logfiles[config->nlogfiles];
        if (pattern[strlen(pattern) - 1] == '\n')
        {
            pattern[strlen(pattern) - 1] = '\0';
        }

        /* glob fname, if not successfull just copy pattern as filename */
        if (glob_fname(pattern, cfg_file) != 0)
        {
            cfg_file->log_fname = strdup(pattern);
            cfg_file->exists = access(cfg_file->log_fname, R_OK) ? false : true;
            if (cfg_file->exists == false)
            {
                log_warn("Log file %s", cfg_file->log_fname);
            }
        }

        config->nlogfiles++;
    }


    fclose(fd_config);

    return config;
error:
    free_config(config);
    if (fd_config) fclose(fd_config);
    return NULL;
}

int glob_fname(char *pattern, config_file_t *cfg_file)
{
    glob_t *pglob = NULL;

    /* glob may realloc log_fname and adapt size */
    int globres = glob(pattern, GLOB_TILDE, NULL, pglob);
    if (globres != GLOB_NOMATCH)
    {
        if (pglob) globfree(pglob);
        return -1;
    }
    check(globres == 0, "Globbing failed (not due to NOMATCH)");

    char *fname = NULL;
    /* Process glob results */
    for (size_t i = 0; i < pglob->gl_pathc; i++)
    {
        fname = pglob->gl_pathv[i];
        cfg_file->log_fname = strdup(fname);
        cfg_file->exists = access(cfg_file->log_fname, R_OK) ? false : true;
        if (cfg_file->exists == false)
        {
            log_warn("Log file %s", cfg_file->log_fname);
        }
    }
    /* Free pglob */
    if (pglob) globfree(pglob);
    return 0;
error:
    if (pglob) globfree(pglob);
    return -1;
}

void free_config(config_t *config)
{
    if (config)
    {
        for (size_t i = 0; i<max_logfile_array; i++)
        {
            config_file_t cfile = config->logfiles[i];
            if (cfile.log_fname == NULL) break;
            free(cfile.log_fname);
        }
        free(config);
    }
}

void print_config(config_t *config)
{
    if (config)
    {
        printf("Config has %lu logfile entries%c\n",
               config->nlogfiles,
               config->nlogfiles == 0 ? '.' : ':');
        for (size_t i = 0; i<max_logfile_array; i++)
        {
            config_file_t cfile = config->logfiles[i];
            if (cfile.log_fname == NULL) break;
            printf("%s %s\n",
                   cfile.log_fname,
                   cfile.exists ? "exists" : "does not exist or read is not permitted");
        }
    }
}
