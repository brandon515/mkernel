#pragma once
#include <stdarg.h>
#include <stdint.h>
#include "kstring.h"
#include "monitor.h"
#include "serial.h"

typedef enum{
    SERIAL,
    STDIO
} device_t;

void printf(device_t device, const char *ascii_string, ...);
