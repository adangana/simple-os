#include "include/resource.h"
#include "include/timesharing.h"
#include <malloc.h>

static list_elem_t *get_ready_list_entry(int p_id);
static list_elem_t *get_resource_list_entry(int p_id, int r_id);

void request(int r_id, int requested) {
  // Requesting a nonexistent resource
  if (r_id >= NUM_RCB) {
    printf("-1 ");
    return;
  }

  // Init process 0 requests a resource
  if (current_process == 0) {
    printf("-1 ");
    return;
  }

  pcb_t *pcb = &pcb_table[current_process];
  rcb_t *rcb = &rcb_table[r_id];
  list_elem_t *r = get_resource_list_entry(current_process, r_id);
  resource_entry_t *r_entry = NULL;

  int held;
  if (r == NULL) {
    held = 0;
  } else {
    r_entry = (resource_entry_t *)r->data;
    held = r_entry->cnt;
  }

  // Requesting to hold more units of resource than available
  if (held + requested > rcb->inventory) {
    printf("-1 ");
    return;
  }

  if (rcb->state >= requested) {
    rcb->state -= requested;

    if (held > 0) // Resource already in process' resource list
    {
      r_entry->cnt += requested;
    } else // Adding resource to process' resource list
    {
      resource_entry_t *new_r_entry =
          (resource_entry_t *)malloc(sizeof(resource_entry_t));
      new_r_entry->id = r_id;
      new_r_entry->cnt = requested;

      list_elem_t *new_r_elem = (list_elem_t *)malloc(sizeof(list_elem_t));
      new_r_elem->data = (void *)new_r_entry;

      list_push_back(&pcb->resources, new_r_elem);
    }

    printf("%d ", current_process);
  } else {
    pcb->state = PROCESS_BLOCKED;

    // Removing current process from ready list
    list_elem_t *elem = get_ready_list_entry(current_process);
    list_remove_elem(elem);
    free(elem->data);

    // Adding current process to wait list of resource
    resource_entry_t *r_entry =
        (resource_entry_t *)malloc(sizeof(resource_entry_t));
    r_entry->id = current_process;
    r_entry->cnt = requested;
    elem->data = (void *)r_entry;

    list_push_back(&rcb->wait_list, elem);

    scheduler();
  }
}

void release(int r_id, int released, int p_id, bool recurring) {
  rcb_t *rcb = &rcb_table[r_id];

  list_elem_t *r_elem = get_resource_list_entry(p_id, r_id);

  // Releasing a resource that the process does not hold
  if (r_elem == NULL) {
    printf("-1 ");
    return;
  }

  resource_entry_t *r_entry = (resource_entry_t *)r_elem->data;

  // Releasing more units of the resource than the process holds
  if (released > r_entry->cnt) {
    printf("-1 ");
    return;
  }

  // If releasing all held units, remove resource from process resources
  if (released == r_entry->cnt) {
    list_remove_elem(r_elem);
    free(r_elem);
    free(r_entry);
  }
  // Otherwise, update just existing resources entry
  else {
    r_entry->cnt -= released;
  }

  rcb->state += released;

  if (!list_empty(&rcb->wait_list)) {
    // Unblock as many processes waiting on resource as possible
    for (list_elem_t *e = list_begin(&rcb->wait_list);
         e != list_tail(&rcb->wait_list);) {
      list_elem_t *next = list_next(e);
      resource_entry_t *r = (resource_entry_t *)e->data;
      pcb_t *pcb = &pcb_table[r->id];

      if (rcb->state >= r->cnt) {
        rcb->state -= r->cnt;

        // Insert resource into new process' resources list
        list_elem_t *r_elem = (list_elem_t *)malloc(sizeof(list_elem_t));
        resource_entry_t *r_entry =
            (resource_entry_t *)malloc(sizeof(resource_entry_t));
        r_entry->id = r_id;
        r_entry->cnt = r->cnt;
        r_elem->data = (void *)r_entry;
        list_push_back(&pcb->resources, r_elem);

        // Unblock process and remove from resource wait list
        pcb->state = PROCESS_READY;
        list_remove_elem(e);

        int *tmp = (int *)malloc(sizeof(int));
        *tmp = r->id;
        free(r);
        e->data = (void *)tmp;

        // Move process to ready list
        list_t *rl = &ready_lists[pcb->priority];
        list_push_back(rl, e);
      }

      e = next;
    }

    if (!recurring)
      scheduler();
  } else {
    if (!recurring)
      printf("%d ", current_process);
  }
}

static list_elem_t *get_ready_list_entry(int p_id) {
  list_t *rl = &ready_lists[pcb_table[p_id].priority];

  for (list_elem_t *e = list_begin(rl); e != list_tail(rl); e = list_next(e)) {
    int id = *(int *)e->data;
    if (id == p_id)
      return e;
  }

  return NULL;
}

static list_elem_t *get_resource_list_entry(int p_id, int r_id) {
  list_t *rl = &pcb_table[p_id].resources;

  for (list_elem_t *e = list_begin(rl); e != list_tail(rl); e = list_next(e)) {
    resource_entry_t *r = (resource_entry_t *)e->data;
    if (r->id == r_id)
      return e;
  }

  return NULL;
}
