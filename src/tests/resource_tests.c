#include <stdio.h>
#include <assert.h>
#include "../include/resource.h"
#include "../include/process.h"
#include "../include/init.h"
#include "../include/timesharing.h"

void test_request_easy (void)
{
    init ();
    
    create (PRIORITY_MEDIUM);
    assert (current_process == 1);

    request (0, 1);
    assert (!list_empty (&pcb_table[current_process].resources));
    assert (rcb_table[0].state == 0);

    list_elem_t *r_elem = list_begin (&pcb_table[current_process].resources);
    resource_entry_t *r_entry = (resource_entry_t *) r_elem->data;
    assert (r_entry->id == 0);

    printf ("test_request_easy passed\n");
}

void test_request_medium (void)
{
    init ();
    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);
    assert (current_process == 1);

    request (0, 1);
    timeout ();
    assert (current_process == 2);
    request (0, 1);

    assert (current_process == 1);
    assert (pcb_table[2].state == PROCESS_BLOCKED);
    assert (list_size (&rcb_table[0].wait_list) == 1);

    printf ("test_request_block passed\n");
}

void test_request_hard (void)
{
    init ();
    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);

    assert (current_process == 1);

    request (2, 2);
    assert (!list_empty (&pcb_table[1].resources));
    timeout ();

    assert (current_process == 2);
    request (2, 1);
    assert (!list_empty (&rcb_table[2].wait_list));
    assert (pcb_table[2].state == PROCESS_BLOCKED);
    timeout ();
    timeout ();

    assert (current_process == 3);
    request (2, 1);
    assert (list_size (&rcb_table[2].wait_list) == 2);
    assert (pcb_table[3].state == PROCESS_BLOCKED);

    printf ("test_request_hard passed\n");
}

void test_release_easy (void)
{
    init ();
    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);

    request (0, 1);
    timeout ();
    request (0, 1);
    timeout ();

    printf ("expected output: error\n");
    printf ("actual output: ");
    release (0, 2);

    release (0, 1);

    assert (pcb_table[2].state == PROCESS_READY);
    assert (list_empty (&rcb_table[0].wait_list));

    printf ("test_release_easy passed\n");
}

void test_release_medium (void)
{
    init ();
    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);
    create (PRIORITY_MEDIUM);

    request (2, 2);
    timeout ();

    request (2, 1);
    timeout ();
    timeout ();

    request (2, 1);
    timeout ();

    assert (list_size (&rcb_table[2].wait_list) == 2);
    assert (pcb_table[1].state == PROCESS_READY);
    assert (pcb_table[2].state == PROCESS_BLOCKED);
    assert (pcb_table[3].state == PROCESS_BLOCKED);

    release (2, 2);

    assert (list_empty (&rcb_table[2].wait_list));
    assert (pcb_table[1].state == PROCESS_READY);
    assert (pcb_table[2].state == PROCESS_READY);
    assert (pcb_table[3].state == PROCESS_READY);

    printf ("test_release_medium passed\n");
}

int main (void) 
{
    test_request_easy ();
    printf ("\n");

    test_request_medium ();
    printf ("\n");

    test_request_hard ();
    printf ("\n");

    test_release_easy ();
    printf ("\n");

    test_release_medium ();
    printf ("\n");

    return 0;
}
