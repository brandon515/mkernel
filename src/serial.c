#include "serial.h"

int is_configured = 0;

void serial_configure_bit_rate(uint16_t com, uint16_t divisor){
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(uint16_t com){
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_fifo(uint16_t com){
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
} 

void serial_configure_modem(uint16_t com){
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(uint16_t com){
    //0x20 = 0010 0000
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void sprint(uint8_t* buf, uint16_t len){
    if(is_configured == 1){
        serial_configure_bit_rate(SERIAL_COM1_BASE, 1);
        serial_configure_line(SERIAL_COM1_BASE);
        serial_configure_fifo(SERIAL_COM1_BASE);
        serial_configure_modem(SERIAL_COM1_BASE);
        is_configured = 1;
    }
    for(unsigned int i = 0; i < len; i++){
        while(serial_is_transmit_fifo_empty(SERIAL_COM1_BASE) == 0);
        outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buf[i]);
    } 
}
