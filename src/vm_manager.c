#include "include/vm_manager.h"
#include "include/globals.h"
#include "include/list.h"
#include <stdlib.h>

/* Initializes segment table entry for a given segment */
static void initialize_segment(int segment, int length, int frame) {
  phys_mem[2 * segment] = length;
  phys_mem[2 * segment + 1] = frame;
}

/* Initializes page table entry for a given page of a segment */
static void initialize_page(int segment, int page, int frame) {
  phys_mem[phys_mem[2 * segment + 1] * BLOCK_SIZE + page] = frame;
}

/* Reads integer from input into location specified by dest */
static int parse_input(int cur, int *dest) {
  while (cur == ' ')
    cur = getchar();
  while (cur >= '0' && cur <= '9') {
    *dest = *dest * 10 + (cur - '0');
    cur = getchar();
  }
  return cur;
}

void read_block(int b, int m) {
  for (int i = 0; i < BLOCK_SIZE; i++)
    phys_mem[m * BLOCK_SIZE + i] = disk[b][i];
}

void vm_init(void) {
  // Initializing free frame list
  list_init(&free_frames);
  for (int i = 2; i < NUM_BLOCKS; i++) {
    list_elem_t *tmp_elem = (list_elem_t *)malloc(sizeof(list_elem_t));
    int *tmp_data = (int *)malloc(sizeof(int));
    *tmp_data = i;
    tmp_elem->data = tmp_data;

    list_push_back(&free_frames, tmp_elem);
  }

  int cur = getchar();

  while (cur != '\n' && cur != EOF) {
    int segment = 0, length = 0, frame = 0;

    cur = parse_input(cur, &segment);
    cur = parse_input(cur, &length);
    cur = parse_input(cur, &frame);

    // Updating free frame list
    list_elem_t *removed = list_remove_id(&free_frames, frame);
    free(removed->data);
    free(removed);

    initialize_segment(segment, length, frame);
  }

  if (cur == '\n')
    cur = getchar();

  while (cur != '\n' && cur != EOF) {
    int segment, page, frame;

    cur = parse_input(cur, &segment);
    cur = parse_input(cur, &page);
    cur = parse_input(cur, &frame);

    // Updating free frame list
    list_elem_t *removed = list_remove_id(&free_frames, frame);
    free(removed->data);
    free(removed);

    initialize_page(segment, page, frame);
  }
}
