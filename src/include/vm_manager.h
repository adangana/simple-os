#ifndef VM_MANAGER_H
#define VM_MANAGER_H

#include <stdio.h>

/* Copies block b from the disk into frame starting at address m of physical
 * memory */
void read_block(int b, int m);

/* Inititalizes VM from input */
void vm_init(FILE *fp);

/* Translate VA to corresponding PA. Reports error if VA is invalid */
int translate_va(int va);

/* Frees all dynamically allocted data used for VM management */
void vm_cleanup(void);

#endif
