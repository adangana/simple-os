#include "include/vm_manager.h"
#include "include/globals.h"
#include "include/list.h"
#include <stdbool.h>
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
static int parse_input(int cur, int *dest, FILE *fp) {
  bool negative = 0;

  // Skip whitespace in between numbers
  while (cur == ' ')
    cur = fgetc(fp);

  // Account for negative numbers
  if (cur == '-') {
    negative = 1;
    cur = fgetc(fp);
  }

  // Parse number
  while (cur >= '0' && cur <= '9') {
    *dest = *dest * 10 + (cur - '0');
    cur = fgetc(fp);
  }

  if (negative)
    *dest = -(*dest);

  return cur;
}

void read_block(int b, int m) {
  for (int i = 0; i < BLOCK_SIZE; i++)
    phys_mem[m * BLOCK_SIZE + i] = disk[b][i];
}

void vm_init(FILE *fp) {
  // Initializing free frame list
  list_init(&free_frames);
  for (int i = 2; i < NUM_BLOCKS; i++) {
    list_elem_t *tmp_elem = (list_elem_t *)malloc(sizeof(list_elem_t));
    int *tmp_data = (int *)malloc(sizeof(int));
    *tmp_data = i;
    tmp_elem->data = tmp_data;

    list_push_back(&free_frames, tmp_elem);
  }

  int cur = fgetc(fp);

  while (cur != '\n' && cur != EOF) {
    int segment = 0, length = 0, frame = 0;

    cur = parse_input(cur, &segment, fp);
    cur = parse_input(cur, &length, fp);
    cur = parse_input(cur, &frame, fp);

    // Updating free frame list
    if (frame > 0) {
      list_elem_t *removed = list_remove_id(&free_frames, frame);
      free(removed->data);
      free(removed);
    }
    initialize_segment(segment, length, frame);
  }

  if (cur == '\n')
    cur = fgetc(fp);

  while (cur != '\n' && cur != EOF) {
    int segment = 0, page = 0, frame = 0;

    cur = parse_input(cur, &segment, fp);
    cur = parse_input(cur, &page, fp);
    cur = parse_input(cur, &frame, fp);

    int segment_frame = phys_mem[2 * segment + 1];

    /* If segment PT is not in physical memory, initialize its pages in the
     * specified paging disk block */
    if (segment_frame < 0) {
      disk[-segment_frame][page] = frame;
    } else {
      // Updating free frame list
      if (frame > 0) {
        list_elem_t *removed = list_remove_id(&free_frames, frame);
        free(removed->data);
        free(removed);
      }
      initialize_page(segment, page, frame);
    }
  }
}

void vm_cleanup(void) { free_list(&free_frames); }
