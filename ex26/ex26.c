#include "ex26_args.h"
#include "dbg.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    search_t *search = read_args(argc, argv);
    check(search != NULL, "Reading search arguments failed.");
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
    return 0;
error:
    return -1;
}
