#include <stdio.h>
#include <assert.h>
#include "../include/process.h"
#include "../include/manager.h"
#include "../include/timesharing.h"

void test_create_process_easy (void)
{
    init ();

    assert (current_process == 0);

    create (PRIORITY_MEDIUM);
    assert (current_process == 1);

    for (int i = PRIORITY_LOW; i < PRIORITY_HIGH; i++)
        assert (list_size (&ready_lists[i]) == 1);

    assert (list_empty (&ready_lists[2]));

    printf ("test_create_process_easy passed \n");
}

void test_create_process_medium (void)
{
    init ();

    create (PRIORITY_MEDIUM);
    assert (current_process == 1);

    create (PRIORITY_MEDIUM);
    assert (current_process == 1);

    create (PRIORITY_HIGH);
    assert (current_process == 3);

    create (PRIORITY_HIGH);
    assert (current_process == 3);

    assert (list_size (&ready_lists[0]) == 1);
    assert (list_size (&ready_lists[1]) == 2);
    assert (list_size (&ready_lists[2]) == 2);

    printf ("test_create_process_medium passed\n");
}

void test_destroy_single_process (void)
{
    init ();

    create (PRIORITY_HIGH);
    create (PRIORITY_MEDIUM);
    destroy (2, 0);

    assert (current_process == 1);
    assert (list_empty (&ready_lists[1]));

    printf ("test_destroy_process_easy passed\n");
}

void test_destroy_process_with_children (void)
{
    init ();

    create (PRIORITY_HIGH);
    create (PRIORITY_HIGH);

    timeout ();
    assert (current_process == 2);

    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);
    assert (list_size (&pcb_table[2].children) == 3);

    timeout ();
    assert (current_process == 1);

    destroy (2, 0);

    assert (pcb_table[2].state == PROCESS_UNINITIALIZED);
    assert (pcb_table[3].state == PROCESS_UNINITIALIZED);
    assert (pcb_table[4].state == PROCESS_UNINITIALIZED);
    assert (pcb_table[5].state == PROCESS_UNINITIALIZED);

    printf ("test_destroy_process_with_children passed\n");
}

int main (void)
{
    test_create_process_easy ();
    printf ("\n");

    test_create_process_medium ();
    printf ("\n");

    test_destroy_single_process ();
    printf ("\n");
    
    test_destroy_process_with_children ();

    return 0;
}
