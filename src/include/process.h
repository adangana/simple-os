#ifndef PROCESS_H
#define PROCESS_H

#include "globals.h"
#include <stdbool.h>
#include <stdint.h>

void create(priority_t level);

int destroy(int p_id, bool recurring);

#endif
