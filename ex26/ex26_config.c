#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <glob.h>
#include "ex26_config.h"
#include "ex26_utils.h"
#include "dbg.h"

const size_t max_log_fname = MAX_LOG_FNAME;
const size_t max_logfile_array = MAX_LOGFILE_ARRAY;

/* prototypes */
int glob_fname(char *log_fname, config_t *config);
int config_new_logfile(config_t *config, const char *fname);

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
        strip_trailing_newline(pattern);
        /* glob fname, if not successfull just copy pattern as filename */
        if (glob_fname(pattern, config) != 0)
        {
            int ret = config_new_logfile(config, pattern);
            if (ret != 0) log_warn("globbing results not finished: %s", pattern);
        }
    }


    fclose(fd_config);

    return config;
error:
    free_config(config);
    if (fd_config) fclose(fd_config);
    return NULL;
}

int glob_fname(char *pattern, config_t *config)
{
    glob_t *pglob = calloc(1, sizeof(glob_t));
    check(pglob, "Allocation for glob_t failed.");

    /* glob may realloc log_fname and adapt size */
    int globres = glob(pattern, GLOB_TILDE, NULL, pglob);
    if (globres == GLOB_NOMATCH)
    {
        // for GLOB_NOMATCH no message is necessary, so not with check
        if (pglob) globfree(pglob);
        free(pglob);
        return -1;
    }
    check(globres == 0, "Globbing failed (not due to NOMATCH)");

    char *fname = NULL;
    /* Process glob results */
    for (size_t i = 0; i < pglob->gl_pathc; i++)
    {
        fname = pglob->gl_pathv[i];
        int ret = config_new_logfile(config, fname);
        check(ret == 0, "globbing results not finished");
    }
    /* Free pglob */
    if (pglob) globfree(pglob);
    free(pglob);
    return 0;
error:
    if (pglob) globfree(pglob);
    free(pglob);
    return -1;
}

int config_new_logfile(config_t *config, const char *fname)
{
    check(config->nlogfiles < max_logfile_array, "logfile array full");

    config_file_t *cfg_file = &config->logfiles[config->nlogfiles];
    config->nlogfiles++;
    cfg_file->log_fname = strdup(fname);
    cfg_file->exists = access(cfg_file->log_fname, R_OK) == 0 ? true : false;
    return 0;
error:
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
                   cfile.exists
                   ? "exists and is readable"
                   : "does not exist or read not permitted");
        }
    }
}
