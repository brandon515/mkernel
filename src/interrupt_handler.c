#include "interrupt_handler.h"

void isr_handler(interrupt_state_t params)
{
    printf(STDIO, "interrupt recieved: %u\n", params.int_no);
}
