#include "ex22.h"
#include "dbg.h"
#include <stdlib.h>

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
    log_info("count is: %d", count);

    if (count > 10)
    {
        int numbers = 100;	// BAD! BUGS!

        log_info("count in this scope is %d", numbers);
    }

    log_info("count is at exit: %d", count);

    count = 3000;

    log_info("count after assign: %d", count);
}

int main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    struct State *state = calloc(1, sizeof(struct State));
    check(state != NULL, "allocation of struct State failed");

    // test out THE_AGE accessors
    log_info("My name: %s, age: %d", MY_NAME, get_age(state));

    set_age(state, 100);

    log_info("My age is now: %d", get_age(state));

    // test out THE_SIZE extern
    log_info("THE_SIZE is: %d", state->the_size);
    print_size(state);

    state->the_size = 9;

    log_info("THE SIZE is now: %d", state->the_size);
    print_size(state);

    // test the ratio function static
    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    // test the scope demo
    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("count after calling scope_demo: %d", count);

    return 0;
error:
    if (state != NULL) free(state);
    return 1;
}
