#ifndef EX26_ARGS_H
#define EX26_ARGS_H

#include <stdlib.h>

#define MAX_SEARCH_ARGS 100
#define MAX_LENGTH_SEARCH_ARGS 100
extern const size_t max_search_args;
extern const size_t max_length_search_args;

typedef struct Search
{
    size_t nr_search_args;
    char *search_arg[MAX_SEARCH_ARGS];
    _Bool and_args;
} search_t;

search_t *read_args(int argc, char *argv[]);
void free_search_struct(search_t *search);
void print_args(search_t *search);

#endif
