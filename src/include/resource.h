#ifndef RESOURCE_H
#define RESOURCE_H

#include <stdint.h>
#include "globals.h"

void request (uint8_t r_id, uint8_t requested);

void release (uint8_t r_id, uint8_t released, uint8_t p_id, uint8_t recurring);

#endif
