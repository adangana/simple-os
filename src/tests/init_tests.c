#include "../include/manager.h"
#include "../include/vm_manager.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>

void test_initialization(void) {
  init();

  assert(list_size(&ready_lists[0]) == 1);
  assert(*(uint8_t *)list_begin(&ready_lists[0])->data == 0);

  for (int i = 1; i < NUM_PRIORITY_LEVELS; i++) {
    assert(list_empty(&ready_lists[i]));
  }

  assert(current_process == 0);
  assert(pcb_table[0].priority == PRIORITY_LOW);
  assert(pcb_table[0].state == PROCESS_READY);
  assert(pcb_table[0].parent == INVALID_INDEX);
  assert(list_empty(&pcb_table[0].children));

  for (int j = 1; j < NUM_PCB; j++) {
    assert(pcb_table[j].priority == PRIORITY_UNINITIALIZED);
    assert(pcb_table[j].state == PROCESS_UNINITIALIZED);
    assert(pcb_table[j].parent == INVALID_INDEX);
    assert(list_empty(&pcb_table[j].children));
    assert(list_empty(&pcb_table[j].resources));
  }

  for (int k = 0; k < NUM_RCB; k++) {
    if (k <= 1)
      assert(rcb_table[k].inventory == 1);
    else
      assert(rcb_table[k].inventory == k);

    assert(rcb_table[k].state == rcb_table[k].inventory);
    assert(list_empty(&rcb_table[k].wait_list));
  }

  printf("test_initialization passed\n");

  cleanup();
}

void test_vm_initialization_1(void) {
  FILE *file = fopen("inputs/sample_vm_init_1.txt", "r");
  if (!file) {
    perror("Could not open file");
    printf("test_vm_initialization_1 failed\n");
    return;
  }

  init();
  vm_init(file);

  fclose(file);

  assert(phys_mem[12] == 3000);
  assert(phys_mem[13] == 4);
  printf("%d\n", phys_mem[4 * BLOCK_SIZE + 5]);
  assert(phys_mem[phys_mem[13] * BLOCK_SIZE + 5] == 9);

  printf("test_vm_initialization_1 passed\n");

  cleanup();
  vm_cleanup();
}

void test_vm_initialization_2(void) {
  FILE *file = fopen("inputs/sample_vm_init_2.txt", "r");
  if (!file) {
    perror("Could not open file");
    printf("test_vm_initialization_2 failed\n");
    return;
  }

  init();
  vm_init(file);

  fclose(file);

  assert(phys_mem[16] == 4000);
  assert(phys_mem[17] == 3);
  assert(phys_mem[18] == 5000);
  assert(phys_mem[19] == -7);

  assert(phys_mem[phys_mem[17] * BLOCK_SIZE + 0] == 10);
  assert(phys_mem[phys_mem[17] * BLOCK_SIZE + 1] == -20);
  assert(disk[7][0] == 13);
  assert(disk[7][1] == -25);

  printf("test_vm_initialization_2 passed\n");

  cleanup();
  vm_cleanup();
}

int main(void) {
  test_initialization();
  printf("\n");

  test_vm_initialization_1();
  printf("\n");

  test_vm_initialization_2();
  printf("\n");

  return 0;
}
