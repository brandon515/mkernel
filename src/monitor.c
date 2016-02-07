#include "monitor.h"

uint16_t screen_cursor = 0;
uint16_t buffer_length = 0;
uint8_t terminal_color = 0x07;
//20 times the screen should be more than enough for anything including user space
uint8_t terminal_buffer[SCREEN_WIDTH*SCREEN_HEIGHT*20]; 

uint8_t fb_get_color(uint8_t bg, uint8_t lc){
    return (((bg & 0x0F) << 4) | (lc & 0x0F));
}

uint16_t fb_get_character(uint8_t letter, uint8_t color){
    return ((color&0x0FF)<<8) | (letter&0x0FF);
}

int32_t fb_clear_monitor(){
    for(uint32_t i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++){
        uint16_t clear_character = fb_get_character(' ', terminal_color);
        int32_t ret = fb_write_cell(i,clear_character);
        if(ret > 0){
            return ret;
        }
    }
    return 0;
}

int32_t fb_write_cell(uint32_t i, uint16_t character){
    if(i >= SCREEN_HEIGHT*SCREEN_WIDTH){
        return 1;
    }
    uint16_t *fb = (uint16_t*) 0x000B8000;
    //multiply by 2 because each letter is described with 2 bytes
    fb[i] = character;
    return 0;
}

//FB_WRITE_ARRAY: writes an array to the screen
//  PARAMETERS:
//      uint8_t *buf: an array of ascii letters
//      uint8_t color: the color for all the letters in the array
//      uint16_t len: the length of the array of letters
//      uint16_t cursor: the position to write the letters onto the screen
int32_t fb_write_array(uint8_t *buf, uint8_t color, uint16_t len, uint16_t cursor){
    uint16_t func_cursor = cursor;
    for(uint16_t i = 0; i < len; i++){
        if(buf[i] == '\n'){
            if(func_cursor+(SCREEN_WIDTH-(func_cursor%SCREEN_WIDTH)) >= SCREEN_WIDTH*SCREEN_HEIGHT){
                return -1;
            }
            func_cursor+=(SCREEN_WIDTH-(func_cursor%SCREEN_WIDTH));
            continue;
        }else if(buf[i] == '\t'){
            if(func_cursor+func_cursor%TAB_LENGTH >= SCREEN_WIDTH*SCREEN_HEIGHT){
                return -1;
            }
            func_cursor+=func_cursor%TAB_LENGTH;
            continue;
        }
        uint16_t character = fb_get_character(buf[i], color);
        uint32_t ret = fb_write_cell(func_cursor, character);
        if(ret != 0){
            return -1;
        }
        func_cursor+=1;
    }
    return func_cursor-cursor;
}

int32_t fb_set_cursor(uint16_t i){
    if(i >= SCREEN_WIDTH*SCREEN_HEIGHT){
        return 1;
    }
    uint8_t pos_high = (i >> 8) & 0x00FF;
    uint8_t pos_low = i & 0x00FF;
    outb(FB_COMMAND_PORT, CURSOR_HIGH_BYTE);
    outb(FB_DATA_PORT, pos_high);
    outb(FB_COMMAND_PORT, CURSOR_LOW_BYTE);
    outb(FB_DATA_PORT, pos_low);
    return 0;
}

//the terminal_buffer is just a straight data dump, so "sadf\tsdfa" is not "sadf    sdfa" it is simply "sadf\tsdfa"
//so to translate that when we scrol up you need this method which adds SCREEN_WIDTH to the amount we backtrack
uint32_t terminal_back_track(uint32_t amount_to_backtrack){
    uint32_t ret = 0;
    uint32_t amount_backtracked = 0;
    for(uint32_t i = 0; i < amount_to_backtrack; i++){
        if(terminal_buffer[buffer_length-i] == '\n'){
            amount_backtracked+=SCREEN_WIDTH;
        }else if(terminal_buffer[buffer_length-i] == '\t'){
            amount_backtracked+=4;
        }
        ret +=1;
        if(amount_backtracked >= amount_to_backtrack){
            return ret;
        }
    }
    return ret;
}


int32_t kprint(uint8_t *buf, uint32_t len){
    for(uint32_t i = 0; i < len; i++){
        terminal_buffer[buffer_length] = buf[i];
        buffer_length+=1;
    }
    int32_t cursor_delta = fb_write_array(buf, terminal_color, len, screen_cursor);
    while(cursor_delta == -1){
        uint32_t terminal_delta = terminal_back_track(SCREEN_WIDTH);

        buffer_length-=terminal_delta;
        for(uint32_t i = 0; i < buffer_length; i++){
            terminal_buffer[i] = terminal_buffer[i+terminal_delta];
        }
        fb_clear_monitor();
        cursor_delta = fb_write_array(terminal_buffer, terminal_color, buffer_length, 0);
    }
    screen_cursor+=cursor_delta;
    fb_set_cursor(screen_cursor);
    return 0;
}
