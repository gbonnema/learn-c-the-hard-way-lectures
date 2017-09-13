#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "ex26_config.h"
#include "dbg.h"


const size_t max_name_lengthr = MAX_NAME_LENGTH;
const size_t max_logfile_array = MAX_LOGFILE_ARRAY;
const char *config_name = ".logfind";

config_t *read_config()
{

    FILE *fd_config = NULL;

    config_t *config = calloc(1, sizeof(config_t));
    check(config, "Allocation of config struct failed");

    check(access(config_name, R_OK) == 0,
          "Config file %s does not exist or user has no read access", config_name);

    fd_config = fopen(config_name, "r");
    check(fd_config, "Configuration file %s would not open", config_name);

    fclose(fd_config);

    return config;
error:
    if (config) free(config);
    if (fd_config) fclose(fd_config);
    return NULL;
}
