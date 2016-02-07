#pragma once

#include "io.h"

//IO ports

#define SERIAL_COM1_BASE        0X3F8

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

//IO commands

#define SERIAL_LINE_ENABLE_DLAB         0x80

//IO functions

//Com:  the port we're speaking on, there are 4
//          COM1: 0x3F8
//          COM2: 0x2F8
//          COM3: 0x3E8
//          COM4: 0x2E8
//Divisor:  the default bit rate of a serial port is 115200 Hz, the divisor is what that is divided by.
//          so a 1 would be 115200 Hz and a 2 would be 57600 Hz
void serial_configure_bit_rate(uint16_t com, uint16_t divisor);
void serial_configure_line(uint16_t com);
void serial_configure_fifo(uint16_t com);
void serial_configure_modem(uint16_t com);
int serial_is_transmit_fifo_empty(uint16_t com);
void sprint(uint8_t* buf, uint16_t len);
extern int is_configured;
