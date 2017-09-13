#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "ex26_config.h"
#include "dbg.h"

const size_t max_log_fname = MAX_LOG_FNAME;
const size_t max_logfile_array = MAX_LOGFILE_ARRAY;

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

    char log_fname[MAX_LOG_FNAME] = { 0 };
    char *ret = NULL;
    while((ret = fgets(log_fname, max_log_fname, fd_config)))
    {
        /* process log_fname */
        config_file_t *cfg_file = &config->logfiles[config->nlogfiles];

        cfg_file->log_fname = strdup(log_fname);
        cfg_file->exists = access(cfg_file->log_fname, R_OK) == 0 ? true : false;

        config->nlogfiles++;
    }


    fclose(fd_config);

    return config;
error:
    free_config(config);
    if (fd_config) fclose(fd_config);
    return NULL;
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
            printf("%s %s\n", cfile.log_fname, cfile.exists ? "exists" : "does not exist");
        }
    }
}
