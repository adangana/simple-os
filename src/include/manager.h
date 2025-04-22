#include <stdint.h>
#include "lib/list.h"

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
priority_level_t;

/* Number of resource units. */
typedef enum
{
    ZERO_UNITS,
    ONE_UNITS,
    TWO_UNITS,
    THREE_UNITS
}
resource_units_t;

/* An entry in the Process Control Block (PCB) table. */
typedef struct 
{
    const priority_level_t priority;  // Process priority level.
    process_state_t state;            // Process state.
    uint8_t parent;                   // PCB table index of parent process.
    list_t* children;                 /* Linked list of indices of child
                                         process. */
} 
pcb_entry_t;

/* An entry in the Resource Control Block (RCB) table. */
typedef struct
{
    const resource_units_t inventory;  // Inital number of units (1, 2, or 3).
    resource_units_t state;            // Number of units available.
    list_t *waitlist;                  /* Linked list of process indices and 
                                          how many units they requested. */
}
rcb_entry_t;
