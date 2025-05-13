#include "include/manager.h"
#include "include/globals.h"
#include <stdio.h>
#include <stdlib.h>

void init(void) {
  // Initializing ready lists
  for (int i = 0; i < NUM_PRIORITY_LEVELS; i++) {
    list_init(&ready_lists[i]);
  }

  /* Initializing the init process. Note that its resources list is left
     uninitialized, thus accessing it has undefined behavior. */
  pcb_table[0].priority = PRIORITY_LOW;
  pcb_table[0].state = PROCESS_READY;
  pcb_table[0].parent = INVALID_INDEX;
  list_init(&pcb_table[0].children);

  // Pushing init process to low priority ready list
  list_elem_t *init_elem = (list_elem_t *)malloc(sizeof(list_elem_t));
  uint8_t *tmp = (uint8_t *)malloc(sizeof(uint8_t));
  *tmp = 0;
  init_elem->data = (void *)tmp;
  list_push_back(&ready_lists[0], init_elem);
  current_process = 0;

  // Initializing PCB table
  for (int j = 1; j < NUM_PCB; j++) {
    pcb_table[j].priority = PRIORITY_UNINITIALIZED;
    pcb_table[j].state = PROCESS_UNINITIALIZED;
    pcb_table[j].parent = INVALID_INDEX;
    list_init(&pcb_table[j].children);
    list_init(&pcb_table[j].resources);
  }

  // Initializing RCB table
  for (int k = 0; k < NUM_RCB; k++) {
    rcb_table[k].inventory = (k >= 1) ? k : 1;
    rcb_table[k].state = rcb_table[k].inventory;
    list_init(&rcb_table[k].wait_list);
  }

  printf("%d ", current_process);
}

void cleanup(void) {
  // Free PCB entries
  free_list(&pcb_table[0].children);
  for (int i = 1; i < NUM_PCB; i++) {
    list_t *children = &pcb_table[i].children;
    list_t *resources = &pcb_table[i].resources;
    if (!list_empty(children))
      free_list(&pcb_table[i].children);
    if (i > 0 && !list_empty(resources))
      free_list(&pcb_table[i].resources);
  }

  // Free RCB entries
  for (int j = 0; j < NUM_RCB; j++) {
    list_t *wait_list = &rcb_table[j].wait_list;
    if (!list_empty(wait_list))
      free_list(&rcb_table[j].wait_list);
  }

  // Free ready lists
  for (int k = 0; k < NUM_PRIORITY_LEVELS; k++) {
    list_t *ready_list = &ready_lists[k];
    if (!list_empty(ready_list))
      free_list(&ready_lists[k]);
  }
}
