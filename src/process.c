#include <stdlib.h>
#include <stdio.h>
#include "include/process.h"
#include "include/resource.h"
#include "include/timesharing.h"

void create (priority_t level)
{
    uint8_t id;
    for (id = 1; id < NUM_PCB; id++)
    {
        if (pcb_table[id].priority == PRIORITY_UNINITIALIZED)
            break;
    }

    // Maximum amount of processes reached 
    if (id >= NUM_PCB)
    {
        printf ("error\n");
        return;
    }

    pcb_t *pcb = &pcb_table[id];
    pcb->priority = level;
    pcb->state = PROCESS_READY;
    pcb->parent = current_process;

    // Adding new process to children of current process
    pcb_t *curr_pcb = &pcb_table[current_process];
    list_elem_t *child_elem = (list_elem_t *) malloc (sizeof (list_elem_t));
    uint8_t *tmp1 = (uint8_t *) malloc (sizeof (uint8_t));
    *tmp1 = id;
    child_elem->data = (void *) tmp1;
    list_push_back (&curr_pcb->children, child_elem);

    // Adding new process to appropriate ready list
    list_elem_t *ready_elem = (list_elem_t *) malloc (sizeof (list_elem_t));
    uint8_t *tmp2 = (uint8_t *) malloc (sizeof (uint8_t));
    *tmp2 = id;
    ready_elem->data = (void *) tmp2;
    list_push_back (&ready_lists[level], ready_elem);

    /* Updating id_to_elem global variable to keep track of this ready list 
       wait list element */
    id_to_elem[id] = ready_elem;

    printf ("process %d created\n", id);

    // This will context switch if highest priority process changes 
    scheduler ();
}

/* Destroys a given process and all of its children. Returns the number of
   processes that were destroyed. */
uint8_t destroy (uint8_t p_id, uint8_t recurring)
{
    // Destroying a nonexistent process 
    if (p_id < 0 || p_id >= NUM_PCB)
    {
        printf ("error\n");
        return 0;
    }

    pcb_t *proc = &pcb_table[p_id];

    /* Destroying a process that is not a child process (only checked in 
       first call, not recursive calls) */
    if (!recurring && current_process != proc->parent)
    {
        printf ("error\n");
        return 0;
    }

    uint8_t destroyed = 0;

    // Destroying all child processes
    for (list_elem_t *e = list_begin (&proc->children); 
            e != list_tail (&proc->children); e = list_next (e))
    {
        uint8_t c_id = *(uint8_t *) e->data; 
        destroyed += destroy (c_id, 1);
    }

    // Removing destroyed process from parent's list of children
    pcb_t *parent_proc = &pcb_table[proc->parent];
    free (list_remove_id (&parent_proc->children, p_id));

    // Removing destroyed process from ready list or resource waiting list
    free (list_remove_elem (id_to_elem[p_id]));
    
    // Release all of the destroyed process' resources
    for (list_elem_t *r = list_begin (&proc->resources); 
            r != list_tail (&proc->resources);)
    {
        list_elem_t *next = list_next (r);
        resource_entry_t *r_entry = (resource_entry_t *) r->data;
        release (r_entry->id, r_entry->cnt);
        free (r_entry);
        r = next;
    }

    // Free PCB of process
    proc->priority = PRIORITY_UNINITIALIZED;
    proc->state = PROCESS_UNINITIALIZED;
    proc->parent = INVALID_INDEX;
    
    destroyed += 1;

    printf ("%d processes destroyed\n", destroyed);

    /* Context switch if deleted process releases resource and unblocks a 
       higher level process. */
    if (!recurring)
        scheduler ();

    return destroyed;
}
