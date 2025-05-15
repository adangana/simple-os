#ifndef VM_MANAGER_H
#define VM_MANAGER_H

#include <stdio.h>

/* Copies block b from the disk into frame m of physical memory */
void read_block(int b, int m);

/* Inititalizes VM from input */
void vm_init(FILE *fp);

/* Frees all dynamically allocted data used for VM management */
void vm_cleanup(void);

#endif
