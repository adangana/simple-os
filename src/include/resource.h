#ifndef RESOURCE_H
#define RESOURCE_H

#include "globals.h"
#include <stdbool.h>
#include <stdint.h>

void request(int r_id, int requested);

void release(int r_id, int released, int p_id, bool recurring);

#endif
