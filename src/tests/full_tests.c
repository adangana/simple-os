#include <stdio.h>
#include <assert.h>
#include "../include/manager.h"
#include "../include/process.h"
#include "../include/resource.h"
#include "../include/timesharing.h"

void test_sample_1 (void)
{
    init ();
    create (1);
    create (1);
    create (1);
    timeout ();
    timeout ();
    request (3, 1);
    timeout ();
    request (3, 2);
    timeout ();
    timeout ();
    release (3, 2, current_process, 0);
    cleanup ();
}

void test_sample_2 (void)
{
    init ();
    create (1);
    create (2);
    create (2);
    create (1);
    request (1, 1);
    timeout ();
    request (2, 1);
    request (1, 1);
    request (2, 2);
    destroy (2, 0);
    timeout ();
    cleanup ();
}

void test_slides_example (void)
{
    init ();
    create (1);
    create (1);
    request (0, 1);
    timeout ();
    request (1, 1);
    request (0, 1);
    request (1, 1);
    destroy (1, 0);
    timeout ();
    cleanup ();
}

int main (void) 
{
    test_sample_1 ();
    printf ("\n");
    
    test_sample_2 ();
    printf ("\n");

    test_slides_example ();
    printf ("\n");

    return 0;
}
