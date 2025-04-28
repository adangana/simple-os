#include <stdio.h>
#include "include/timesharing.h"

void scheduler (void)
{
    uint8_t p_id;
    int i;

    // Getting head of first non-empty highest-priority ready list 
    for (i = PRIORITY_HIGH; i >= PRIORITY_LOW; i--)
    {
        if (!list_empty (&ready_lists[i]))
            break;
    }

    p_id = *(uint8_t *) list_begin (&ready_lists[i])->data;
  
    /* If highest priority process is not the current process, perform 
       context switch */
    if (p_id != current_process)
        current_process = p_id;

    printf ("%d ", current_process);
}

void timeout (void)
{
    // Moving current process from head of its RL to end of its RL 
    list_t *rl = &ready_lists[pcb_table[current_process].priority];
    list_elem_t *front = list_pop_front (rl);

    list_push_back (rl, front);
    scheduler ();
}
