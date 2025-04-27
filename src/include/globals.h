#ifndef GLOBALS_H 
#define GLOBALS_H 

#include <stdint.h>
#include "list.h"

#define NUM_PCB 16
#define NUM_RCB 4
#define NUM_PRIORITY_LEVELS 3
#define INVALID_INDEX 255

/* Process state. */
typedef enum
{
    PROCESS_UNINITIALIZED = -1,
    PROCESS_BLOCKED = 0,
    PROCESS_READY = 1
}
process_state_t;

/* Process priority level. */
typedef enum
{
    PRIORITY_UNINITIALIZED = -1,
    PRIORITY_LOW = 0,
    PRIORITY_MEDIUM = 1,
    PRIORITY_HIGH = 2
} 
priority_t;

/* Number of resource units. */
typedef enum
{
    ZERO_UNITS,
    ONE_UNITS,
    TWO_UNITS,
    THREE_UNITS
}
resource_units_t;

/* A Process Control Block (PCB) entry. */
typedef struct 
{
    priority_t priority;    // Process priority level.
    process_state_t state;  // Process state.
    uint8_t parent;         // PCB table index of parent process.
    list_t children;        // Linked list of indices of child processes.
    list_t resources;       /* Linked list of resources that process is
                               currently holding. */
} 
pcb_t;

/* A Resource Control Block (RCB) entry. */
typedef struct
{
    resource_units_t inventory;  // Inital number of units (1, 2, or 3).
    resource_units_t state;      // Number of units available.
    list_t wait_list;             /* Linked list of process indices and 
                                     how many units they requested. */
}
rcb_t;

/* An entry in (1) the held resource list of a process or (2) the wait list of
   a resource. */
typedef struct
{
    uint8_t id;
    uint8_t cnt;
} 
resource_entry_t;

extern list_t ready_lists[NUM_PRIORITY_LEVELS];
extern pcb_t pcb_table[NUM_PCB];
extern rcb_t rcb_table[NUM_RCB];
extern uint8_t current_process;
extern list_elem_t *id_to_elem[NUM_PCB];

#endif

