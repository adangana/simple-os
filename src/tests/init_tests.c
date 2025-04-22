#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "../include/init.h"

void test_initialization (void)
{
    init ();

    assert (list_size (&ready_lists[0]) == 1);
    assert (list_begin (&ready_lists[0])->id == 0);

    for (int i = 1; i < NUM_PRIORITY_LEVELS; i++)
    {
        assert (list_empty (&ready_lists[i]));
    }

    assert (current_process == 0);
    assert (pcb_table[0].priority == PRIORITY_LOW);
    assert (pcb_table[0].state == PROCESS_READY);
    assert (pcb_table[0].parent == INVALID_INDEX);
    assert (list_empty (&pcb_table[0].children));

    for (int j = 1; j < NUM_PCB; j++)
    {
        assert (pcb_table[j].priority == PRIORITY_UNINITIALIZED);
        assert (pcb_table[j].state == PROCESS_UNINITIALIZED);
        assert (pcb_table[j].parent == INVALID_INDEX);
        assert (list_empty (&pcb_table[j].children));
        assert (list_empty (&pcb_table[j].resources));
    }

    for (int k = 0; k < NUM_RCB; k++)
    {
        if (k <= 1)
            assert (rcb_table[k].inventory == 1);
        else
            assert (rcb_table[k].inventory == k);
        
        assert (rcb_table[k].state == rcb_table[k].inventory);
        assert (list_empty (&rcb_table[k].waitlist));
    }

    free (list_begin (&ready_lists[0]));

    printf("test_initialization passed\n");
}

int main (void)
{
    test_initialization ();

    return 0;
}
