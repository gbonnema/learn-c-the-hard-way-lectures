#ifndef EX26_CONFIG_H
#define EX26_CONFIG_H

#include <stdlib.h>

#define MAX_NAME_LENGTH 100
#define MAX_LOGFILE_ARRAY 100

extern const size_t max_name_length;
extern const size_t max_logfile_array;

typedef struct Config
{
    char fname[MAX_NAME_LENGTH];
    char *logfiles[MAX_LOGFILE_ARRAY];
} config_t;

config_t *read_config();

#endif
