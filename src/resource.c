#include "include/resource.h"

void request (uint8_t r_id, uint8_t requested)
{
    rcb_t rcb = rcb_table[r_id];

    if (rcb.state >= requested)
    {
        rcb.state -= requested;
        // TODO: insert r into list of resources of current process
        printf ("resource %d allocated\n", r_id);
    }
    else
    {
    
    }
}

void release (uint8_t r_id, uint8_t released)
{
    // TODO: Implement me
}
