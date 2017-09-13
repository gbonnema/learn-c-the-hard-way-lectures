#ifndef EX26_CONFIG_H
#define EX26_CONFIG_H

#include <stdlib.h>

#define MAX_LOG_FNAME 255
#define MAX_LOGFILE_ARRAY 100

extern const size_t max_log_fname;
extern const size_t max_logfile_array;

typedef struct ConfigFile
{
    char *log_fname;
    _Bool exists;
} config_file_t;

typedef struct Config
{
    size_t nlogfiles;
    config_file_t logfiles[MAX_LOGFILE_ARRAY];
} config_t;

/* prototypes */
config_t *read_config();
void free_config(config_t *config);
void print_config(config_t *config);

#endif
