#include "include/globals.h"
#include "include/manager.h"
#include "include/process.h"
#include "include/resource.h"
#include "include/timesharing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 32

int main(void) {
  char input[INPUT_SIZE];
  uint8_t initialized = 0;
  uint8_t ran = 0;

  while (1) {
    if (!ran) {
      printf("> ");
      ran = 1;
    } else {
      printf("\n> ");
    }

    if (fgets(input, INPUT_SIZE, stdin) == NULL) {
      printf("-1 ");
    }

    input[strcspn(input, "\n")] = 0; // Remove the newline

    if (strncmp(input, "in", 2) == 0) {
      if (initialized)
        cleanup();
      init();
      initialized = 1;
    } else if (strncmp(input, "cr ", 3) == 0) {
      uint8_t p_id = (uint8_t)atoi(input + 3);
      create(p_id);
    } else if (strncmp(input, "de ", 3) == 0) {
      uint8_t p_id = (uint8_t)atoi(input + 3);
      destroy(p_id, 0);
    } else if (strncmp(input, "rq ", 3) == 0) {
      int resource, quantity;
      if (sscanf(input + 3, "%d %d", &resource, &quantity) == 2)
        request((uint8_t)resource, (uint8_t)quantity);
      else
        printf("-1 ");
    } else if (strncmp(input, "rl ", 3) == 0) {
      int resource, quantity;
      if (sscanf(input + 3, "%d %d", &resource, &quantity) == 2)
        release((uint8_t)resource, (uint8_t)quantity, current_process, 0);
      else
        printf("-1 ");
    } else if (strncmp(input, "to", 2) == 0) {
      timeout();
    } else if (strncmp(input, "quit", 4) == 0) {
      if (initialized)
        cleanup();
      break;
    } else {
      printf("-1 ");
    }
  }

  return 0;
}
