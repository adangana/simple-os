#include <stdio.h>
#include <assert.h>
#include "../include/process.h"
#include "../include/init.h"

void test_create_process_easy (void)
{
    init ();

    assert (current_process == 0);

    printf ("expected output:\nprocess 1 created\nprocess 1 is running\n");
    printf("\nactual output:\n");

    create (PRIORITY_MEDIUM);

    assert (current_process == 1);
    for (int i = PRIORITY_LOW; i < PRIORITY_HIGH; i++)
    {
        assert (list_size (&ready_lists[i]) == 1);
    }
    assert (list_empty (&ready_lists[2]));

    printf ("\ntest_create_process_easy passed \n");
}

int main (void)
{
    test_create_process_easy ();

    return 0;
}
