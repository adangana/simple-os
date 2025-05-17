#include "include/input_parser.h"
#include <stdbool.h>

/* Reads integer from input into location specified by dest */
int parse_input(int cur, int *dest, FILE *fp) {
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
