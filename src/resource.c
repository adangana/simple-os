#include <malloc.h>
#include "include/resource.h"
#include "include/timesharing.h"

static list_elem_t *get_ready_list_entry (uint8_t p_id);
static list_elem_t *get_resource_list_entry (uint8_t r_id);

void request (uint8_t r_id, uint8_t requested)
{
    // Requesting a nonexistent resource
    if (r_id < 0 || r_id >= NUM_RCB)
    {
        printf ("error\n");
        return;
    }

    // Init process 0 requests a resource
    if (current_process == 0)
    {
        printf ("error\n");
        return;
    }

    pcb_t *pcb = &pcb_table[current_process]; 
    rcb_t *rcb = &rcb_table[r_id];
    list_elem_t *r = get_resource_list_entry (r_id);
    resource_entry_t *r_entry = NULL;
    
    uint8_t held;
    if (r == NULL)
    {
        held = 0;
    }
    else 
    {
        r_entry = (resource_entry_t *) r->data; 
        held = r_entry->cnt;
    }

    // Requesting to hold more units of resource than available
    if (held + requested > rcb->inventory)
    {
        printf ("error\n");
        return;
    }

    if (rcb->state >= requested)
    {
        rcb->state -= requested;

        if (held > 0)  // Resource already in process' resource list 
        {
            r_entry->cnt += requested;
        }
        else  // Adding resource to process' resource list 
        {
            resource_entry_t *new_r_entry = (resource_entry_t *) malloc 
                (sizeof (resource_entry_t));
            new_r_entry->id = r_id;
            new_r_entry->cnt = requested;

            list_elem_t *new_r_elem = (list_elem_t *) malloc 
                (sizeof (list_elem_t));
            new_r_elem->data = (void *) new_r_entry;

            list_push_back (&pcb->resources, new_r_elem);
        }

        printf ("resource %d allocated\n", r_id);
    }
    else
    {
        pcb->state = PROCESS_BLOCKED;

        // Removing current process from ready list
        list_elem_t *elem = get_ready_list_entry (current_process);
        list_remove_elem (elem);
        free (elem->data);

        // Adding current process to wait list of resource
        resource_entry_t *r_entry = (resource_entry_t *) malloc 
            (sizeof (resource_entry_t));
        r_entry->id = current_process;
        r_entry->cnt = requested;
        elem->data = (void *) r_entry;

        list_push_back (&rcb->wait_list, elem);

        printf ("process %d blocked\n", current_process);

        scheduler ();
    }
}

void release (uint8_t r_id, uint8_t released)
{
    rcb_t *rcb = &rcb_table[r_id];

    list_elem_t *r_elem = get_resource_list_entry (r_id);
    
    // Releasing a resource that the process does not hold
    if (r_elem == NULL)
    {
        printf ("error\n");
        return;
    }

    // Remove r from resource list of process i
    list_remove_elem (r_elem);
    resource_entry_t *r_entry = (resource_entry_t *) r_elem->data;
    free (r_elem);
    free (r_entry);

    rcb->state += released;

    if (!list_empty (&rcb->wait_list))
    {
        // Unblock as many processes waiting on resource as possible
        for (list_elem_t *e = list_begin (&rcb->wait_list); 
                e != list_tail (&rcb->wait_list);)
        {
            list_elem_t *next = list_next (e);
            resource_entry_t *r = (resource_entry_t *) e->data;
            pcb_t *pcb = &pcb_table[r->id];

            if (rcb->state >= r->cnt)
            {
                // Unblock process and move to ready list
                pcb->state = PROCESS_READY;
                list_t *rl = &ready_lists[pcb->priority];
                list_remove_elem (e);
                free (e->data);
                uint8_t *tmp = (uint8_t *) malloc (sizeof (uint8_t));
                e->data = (void *) tmp;
                list_push_back (rl, e);
            }

            e = next;
        }
    }
}

static list_elem_t *get_ready_list_entry (uint8_t p_id)
{
    list_t *rl = &ready_lists[pcb_table[current_process].priority];

    for (list_elem_t *e = list_begin (rl); e != list_tail (rl); 
            e = list_next (e))
    {
        uint8_t id = *(uint8_t *) e->data;
        if (id == p_id)
            return e;
    }

    return NULL;
}

static list_elem_t *get_resource_list_entry (uint8_t r_id)
{
    list_t *rl = &pcb_table[current_process].resources;

    for (list_elem_t *e = list_begin (rl); e != list_tail (rl); 
            e = list_next (e))
    {
        resource_entry_t *r = (resource_entry_t *) e->data;
        if (r->id == r_id)
            return e;
    }

    return NULL;
}

