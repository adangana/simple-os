#include <stdio.h>
#include <assert.h>
#include "../include/timesharing.h"
#include "../include/process.h"
#include "../include/manager.h"

void test_scheduler (void)
{
    init ();

    create (PRIORITY_MEDIUM);
    assert (current_process == 1);

    create (PRIORITY_HIGH);
    assert (current_process == 2);

    printf ("test_scheduler passed\n");
}

void test_timeout_easy (void)
{
    init ();
    list_t *rl = &ready_lists[PRIORITY_MEDIUM];

    create (PRIORITY_MEDIUM);
    assert (current_process == 1);
    assert (list_size (rl) == 1);
    assert (*(uint8_t *) list_begin (rl)->data == 1);
    assert (*(uint8_t *) list_end (rl)->data == 1);

    create (PRIORITY_MEDIUM);
    assert (current_process == 1);
    assert (list_size (rl) == 2);
    assert (*(uint8_t *) list_begin (rl)->data == 1);
    assert (*(uint8_t *) list_end (rl)->data == 2);

    timeout ();
    assert (current_process == 2);
    assert (list_size (rl) == 2);
    assert (*(uint8_t *) list_begin (rl)->data == 2);
    assert (*(uint8_t *) list_end (rl)->data == 1);

    printf ("test_timeout_easy passed\n");
}

void test_timeout_medium (void)
{
    init ();
    list_t *rl = &ready_lists[PRIORITY_MEDIUM];

    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);

    timeout ();
    assert (current_process == 2);
    assert (*(uint8_t *) list_begin (rl)->data == 2);

    timeout ();
    assert (current_process == 3);
    assert (*(uint8_t *) list_begin (rl)->data == 3);

    timeout ();
    assert (current_process == 1);
    assert (*(uint8_t *) list_begin (rl)->data == 1);

    printf ("test_timeout_medium passed\n");
}

int main (void)
{
    test_scheduler ();
    test_timeout_easy ();
    test_timeout_medium ();

    return 0;
}

