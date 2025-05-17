#include "include/input_parser.h"
#include "include/vm_manager.h"
#include <stdbool.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    perror("Provide init file path and input file path");
    return -1;
  }

  char *init_path = argv[1];
  char *input_path = argv[2];

  FILE *init_file = fopen(init_path, "r");
  if (!init_file) {
    perror("Could not open init file");
    return -1;
  }

  FILE *input_file = fopen(input_path, "r");
  if (!input_file) {
    perror("Could not open input file");
    return -1;
  }

  vm_init(init_file);
  fclose(init_file);

  int cur = fgetc(input_file);

  bool first = 1;
  while (cur != '\n' && cur != EOF) {
    int va = 0;
    cur = parse_input(cur, &va, input_file);
    int pa = translate_va(va);

    if (!first)
      printf(" ");

    printf("%d", pa);

    if (first)
      first = 0;
  }

  printf("\n");

  fclose(input_file);
  return 0;
}
