#include "include/globals.h"

list_t ready_lists[NUM_PRIORITY_LEVELS];
pcb_t pcb_table[NUM_PCB];
rcb_t rcb_table[NUM_RCB];
uint8_t current_process;
list_elem_t *id_to_elem[NUM_PCB];

