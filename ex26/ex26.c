#include "ex26_args.h"
#include <stdio.h>
#include "ex26_config.h"
#include "ex26_logfile.h"
#include "dbg.h"

const char *config_name = ".logfind";

int main(int argc, char *argv[])
{
    config_t *config = NULL;
    search_t *search = NULL;

    config = read_config(config_name);
    check(config, "Read of config failed.");

    search = read_args(argc, argv);
    check(search != NULL, "Reading search arguments failed.");

    print_args(search);
    print_config(config);

    for (unsigned i = 0; i < config->nlogfiles; i++)
    {
        if (config->logfiles[i].exists)
        {
            char *fname = config->logfiles[i].log_fname;
            scan_logfile(fname, search);
        }
    }

    free_search_struct(search);
    return 0;
error:
    free_search_struct(search);
    free_config(config);
    return -1;
}
