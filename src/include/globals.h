#ifndef MANAGER_H
#define MANAGER_H

#include <stdint.h>
#include "list.h"

#define NUM_PCB 16
#define NUM_RCB 4
#define NUM_PRIORITY_LEVELS 3

/* Process state. */
typedef enum
{
    PROCESS_BLOCKED,
    PROCESS_READY
}
process_state_t;

/* Process priority level. */
typedef enum
{
    LOW_PRIORITY,
    MEDIUM_PRIORITY,
    HIGH_PRIORITY
} 
priority_t;

/* A Process Control Block (PCB) entry. */
typedef struct 
{
    const priority_t priority;  // Process priority level.
    process_state_t state;            // Process state.
    uint8_t parent;                   // PCB table index of parent process.
    list_t* children;                 /* Linked list of indices of child
                                         process. */
} 
pcb_t;

/* Number of resource units. */
typedef enum
{
    ZERO_UNITS,
    ONE_UNITS,
    TWO_UNITS,
    THREE_UNITS
}
resource_units_t;

/* A Resource Control Block (RCB) entry. */
typedef struct
{
    const resource_units_t inventory;  // Inital number of units (1, 2, or 3).
    resource_units_t state;            // Number of units available.
    list_t *waitlist;                  /* Linked list of process indices and 
                                          how many units they requested. */
}
rcb_t;

extern pcb_t pcb_table[NUM_PCB];
extern rcb_t rcb_table[NUM_RCB];
extern list_t *ready_lists[NUM_PRIORITY_LEVELS];
extern uint8_t current_process;

#endif
