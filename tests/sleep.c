/*
 * Test the sleep function
*/

#include "common.h"

int main(void) {
    int after_time = 0;
    int current_time = time(NULL);

    /* We will sleep for ~3 seconds */
    libproc_sleep(LIBPROC_SLEEP_SECOND * 5);

    after_time = time(NULL);

    /* If the difference is more than 3, we have a problem. */
    if((after_time - current_time) <= 3)
        return 0;

    fprintf(stderr, "Sleep function only slept for %i seconds.\n", (after_time - current_time));
    assert((after_time - current_time) <= 3);
    exit(EXIT_FAILURE);

    return 0;
}
