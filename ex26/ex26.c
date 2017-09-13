#include "ex26_args.h"
#include "ex26_config.h"
#include "dbg.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    config_t *config = NULL;
    search_t *search = NULL;

    config = read_config();
    check(config, "Read of config failed.");

    search = read_args(argc, argv);
    check(search != NULL, "Reading search arguments failed.");

    print_args(search);

    free_search_struct(search);
    return 0;
error:
    // FIXME: search and config need better / deeper free
    free_search_struct(search);
    if (config) free(config);
    return -1;
}
