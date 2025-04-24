#include <stdio.h>
#include <assert.h>
#include "../include/timesharing.h"
#include "../include/process.h"
#include "../include/init.h"

void test_timeout (void)
{
    init ();
    list_t *rl = &ready_lists[PRIORITY_MEDIUM];

    create (PRIORITY_MEDIUM);
    assert (current_process == 1);
    assert (list_size (rl) == 1);
    assert (list_begin (rl)->id == 1);
    assert (list_end (rl)->id == 1);

    create (PRIORITY_MEDIUM);
    assert (current_process == 1);
    assert (list_size (rl) == 2);
    assert (list_begin (rl)->id == 1);
    assert (list_end (rl)->id == 2);

    timeout ();
    assert (current_process == 2);
    assert (list_size (rl) == 2);
    assert (list_begin (rl)->id == 2);
    assert (list_end (rl)->id == 1);

    printf ("test_timeout passed\n");
}

int main (void)
{
    test_timeout ();

    return 0;
}

