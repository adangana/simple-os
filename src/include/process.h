#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include "manager.h"

void create (priority_t level);

void destroy (uint8_t p_id);

#endif
