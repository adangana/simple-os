#include "include/vm_manager.h"
#include "include/globals.h"

void read_block(int b, int m) {
  for (int i = 0; i < BLOCK_SIZE; i++)
    phys_mem[m * BLOCK_SIZE + i] = disk[b][i];
}
