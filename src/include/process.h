#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "globals.h"

void create (priority_t level);

uint8_t destroy (uint8_t p_id);

#endif
