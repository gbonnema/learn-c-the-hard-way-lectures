#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ex26_logfile.h"
#include "ex26_args.h"
#include "dbg.h"

/* prototypes */
_Bool logfile_search(const char*line, search_t *search);

int scan_logfile(const char *fname, search_t *search)
{
    size_t size = 255;
    char *line = calloc(size, sizeof(char));
    check(line, "Allocation failed.");
    FILE *fp = fopen(fname, "r");
    unsigned linenr = 0;
    while(getline(&line, &size, fp) != -1)
    {
        linenr++;
        if (logfile_search(line, search))
        {
            printf("%s %ud: %s", fname, linenr, line);
        }
    }
    fclose(fp);
    return 0;
error:
    free(line);
    return -1;
}

_Bool logfile_search(const char*line, search_t *search)
{
    _Bool found = false;
    if (search->and_args)
    {
        /* Search for and-ed words */
        unsigned i = 0;
        for (i = 0; i < search->nr_search_args; i++)
        {
            char *word = search->search_arg[i];
            char *p = strstr(line, word);
            if (!p) break;	/* Alas, no match */
        }
        if (i == search->nr_search_args)
        {
            found = true;
        }
    }
    else
    {
        /* Search for or-ed words */
        unsigned i = 0;
        for (i = 0; i < search->nr_search_args; i++)
        {
            char *word = search->search_arg[i];
            char *p = strstr(line, word);
            if (p) break;	/* match found: done */
        }
        if (i < search->nr_search_args)
        {
            found = true;
        }
    }
    return found;
}
