#include <stdlib.h>
#include <stdio.h>
#include "ex26_args.h"
#include "dbg.h"

const size_t max_search_args = MAX_SEARCH_ARGS;
const size_t max_length_search_args = MAX_LENGTH_SEARCH_ARGS;

search_t *read_args(int argc, char *argv[])
{
    search_t *search = calloc(1, sizeof(search_t));

    check(argc > 1, "Usage: %s [-o] <search arguments>", argv[0]);

    search->and_args = 1;
    search->nr_search_args = 0;

    for(int i=1; i<argc; i++)
    {
        char *str = argv[i];
        if (strcmp(str, "-o") == 0)
        {
            /* Handle all search argument as being or-ed. */
            search->and_args = 0;
        }
        else
        {
            search->nr_search_args++;
            int sa = search->nr_search_args - 1;
            search->search_arg[sa] = calloc(max_length_search_args, sizeof(char));
            check(search->search_arg[sa] != NULL, "Allocation error for result search argument.");
            char *ret = strcpy(search->search_arg[sa], argv[i]);
            check(ret != NULL, "strcpy from search argument failed.");
        }
    }

    return search;
error:
    free_search_struct(search);
    return NULL;
}

void free_search_struct(search_t *search)
{
    if (search)
    {
        for(size_t i=0; i<max_search_args; i++)
        {
            if (search->search_arg[i] == NULL) break;
            free(search->search_arg[i]);
            search->search_arg[i] = 0;
        }
        free(search);
    }
}

void print_args(search_t *search)
{
    printf("The search terms are:\n");
    char *start = "\t";
    char *and = " & ";
    char *or = " | ";
    char *glue = start;
    for (size_t i=0; i<max_search_args; i++)
    {
        if (!search->search_arg[i]) break;
        printf("%s%s", glue, search->search_arg[i]);
        glue = search->and_args ? and : or;
    }
    printf("\n");
}
