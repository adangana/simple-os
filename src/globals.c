#include "include/globals.h"

list_t ready_lists[NUM_PRIORITY_LEVELS];
pcb_t pcb_table[NUM_PCB];
rcb_t rcb_table[NUM_RCB];
int current_process;
list_elem_t *id_to_elem[NUM_PCB];

int phys_mem[PHYSICAL_MEMORY_SIZE];
int disk[NUM_BLOCKS][BLOCK_SIZE];
list_t free_frames;
