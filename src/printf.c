#include "printf.h"

int characters_printed;
void printc(device_t device, uint8_t character){
    characters_printed++;
    switch(device){
        case SERIAL:
            sprint(&character, 1);
            break;
        case STDIO:
            kprint(&character, 1);
            break;
        default:
            break;
    };
}

char dec_to_char(int number){
    int num = number % 10;
    if(num < 0){
        num *= -1;
    }
    switch(num){
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        default:
            return 'N';
    }
}

char hex_to_char(int number, int use_capital){
    if(number < 0){
        number *= -1;
    }
    if(number < 10){
        return dec_to_char(number);
    }
    switch(number){
        case 10:
            if(use_capital){
                return 'A';
            }else{
                return 'a';
            }
        case 11:
            if(use_capital){
                return 'B';
            }else{
                return 'b';
            }
        case 12:
            if(use_capital){
                return 'C';
            }else{
                return 'c';
            }
        case 13:
            if(use_capital){
                return 'D';
            }else{
                return 'd';
            }
        case 14:
            if(use_capital){
                return 'E';
            }else{
                return 'e';
            }
        case 15:
            if(use_capital){
                return 'F';
            }else{
                return 'f';
            }
        default:
            return 'N';
    }
}

int char_to_number(char num){
    switch(num){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return -1;
    }
}

void print_unsigned_integer(device_t device, unsigned int num){
    if(num == 0){
        printc(device, '0');
    }
    char buffer[32] = {0};
    uint8_t inc = 0;
    while(num != 0){
        buffer[inc] = dec_to_char(num);
        inc++;
        num /= 10;
    }
    for(int j = inc-1; j >= 0; j--){
        printc(device, buffer[j]);
    }
}

void print_signed_integer(device_t device, int num){
    if(num < 0){
        printc(device, '-');
        num *= -1;
    }
    print_unsigned_integer(device, (unsigned int)num);
}

void print_string_characters(device_t device, const char *str){
    int len = strlen(str);
    for(int i = 0; i < len; i++){
        printc(device, str[i]);
    }
}

void print_double(device_t device, double num){
    if(num == 0.0){
        printc(device, '0');
        printc(device, '.');
        printc(device, '0');
    }
    int int_place = (int)num;
    double dec_place = num-int_place;
    char buffer[128];
    uint32_t buffer_pointer = 0;
    while(int_place > 0){
        buffer[buffer_pointer] = dec_to_char(int_place);
        int_place/=10;
        buffer_pointer++;
    }
    for(int i = buffer_pointer-1; i >= 0; i--){
        printc(device, buffer[i]);
    }
    printc(device, '.');
    int prec_place =(int)(dec_place*1000);
    buffer_pointer = 0;
    while(prec_place > 0){
        buffer[buffer_pointer] = dec_to_char(prec_place);
        prec_place/=10;
        buffer_pointer++;
    }
    for(int i = buffer_pointer-1; i >= 0; i--){
        printc(device, buffer[i]);
    }
}

void print_hex(device_t device, unsigned int decimal, int is_capital, unsigned int digits){
    printc(device, '0');
    printc(device, 'x');
    if(decimal == 0){
        for(uint32_t i = 0; i < digits; i++){
            printc(device, '0');
        }
        return;
    }
    char buffer[32];
    uint8_t buffer_pointer = 0;
    while(decimal != 0){
        unsigned int hex_num = decimal & 0x0F;
        decimal = decimal >> 4;
        buffer[buffer_pointer] = hex_to_char(hex_num, is_capital);
        buffer_pointer++;
    }
    if(buffer_pointer < digits){
        unsigned int filler_zeros = digits - buffer_pointer;
        for(unsigned int i = 0; i < filler_zeros; i++){
            printc(device, '0');
        }
    }
    buffer_pointer--;
    while(buffer_pointer > 0){
        printc(device, buffer[buffer_pointer]);
        buffer_pointer--;
    }
    printc(device, buffer[buffer_pointer]);
}

void handle_c(device_t device,va_list *character){
    int c = va_arg(*character, int);
    printc(device, c);
}

void handle_d_or_i(device_t device, va_list *dec){
    int i = va_arg(*dec, int);
    print_signed_integer(device,i);
}

void handle_e_or_E(device_t device, va_list *dec, char e_or_E){
    double i = va_arg(*dec, double);
    uint32_t power_of_ten = 0;
    while(i >= 1){
        power_of_ten++;
        i/=10;
    }
    power_of_ten--;
    i*=10;
    print_double(device, i);
    printc(device, e_or_E);
    print_unsigned_integer(device, power_of_ten);
}    

void handle_f(device_t device, va_list *decimal){
    double num = va_arg(*decimal, double);
    print_double(device,num);
}

void handle_o(device_t device, va_list *dec){
    int decimal = va_arg(*dec, int);
    if(decimal < 0)
    {
        printc(device, '-');
        decimal*=-1;
    }
    printc(device, '0');
    printc(device, 'o');
    int octal_divisor = 1;
    uint32_t octal_number = 0;
    //alright so how this works is you take multiples of 8, starting at 8^0, and keep going up the chain 
    //until you get the highest multiple of 8 that's lower than the number you're converting
    //then you divide it by that multiple of 8, that's your first digit
    //you then take the remainder (here with the % operator) and divide that by the next lower power of 8
    //repeat until you divide by 8^0 and that's your last digit
    //boom, octal number
    while(octal_divisor < decimal){
        octal_divisor*=8;
    }
    octal_divisor/=8;
    while(octal_divisor > 1){
        octal_number += decimal/octal_divisor;
        octal_number *= 10;
        decimal = decimal%octal_divisor;
        octal_divisor /= 8;
    }
    octal_number+= decimal;
    print_unsigned_integer(device, octal_number);
}

void handle_s(device_t device, va_list *str){
    char *string = va_arg(*str, char*);
    print_string_characters(device, string);
}

void handle_u(device_t device, va_list *dec){
    unsigned int num = va_arg(*dec, unsigned int);
    print_unsigned_integer(device, num);
}

void handle_x_or_X(device_t device, va_list *hex, char x_or_X, unsigned int digits){
    unsigned int decimal = va_arg(*hex, unsigned int);
    int is_capital = 1;
    if(x_or_X == 'x'){
        is_capital = 0;
    }
    print_hex(device,decimal,is_capital, digits);
}

void handle_p(device_t device, va_list *ptr, unsigned int digits){
    void *ptr_num = va_arg(*ptr, void*);
    uintptr_t hex_num = (uintptr_t)ptr_num;
    int is_capital = 1;
    print_hex(device, hex_num, is_capital, digits);
}

void handle_n(va_list *ptr){
    int *num = (int*)va_arg(*ptr, void*);
    *num = characters_printed;
}

void printf(device_t device, const char *ascii_string, ...){
    va_list arg;
    va_start(arg, ascii_string);
    size_t len = strlen(ascii_string);
    for(uint32_t i = 0; i < len; i++){
        if(ascii_string[i] == '%'){
            i++;
            switch(ascii_string[i]){
                case 'c':
                    handle_c(device, &arg);
                    break;
                case 'd':
                    handle_d_or_i(device, &arg);
                    break;
                case 'i':
                    handle_d_or_i(device, &arg);
                    break;
                case 'e':
                    handle_e_or_E(device, &arg, 'e');
                    break;
                case 'E':
                    handle_e_or_E(device, &arg, 'E');
                    break;
                case 'f':
                    handle_f(device, &arg);
                    break;
                case 'o':
                    handle_o(device, &arg);
                    break;
                case 's':
                    handle_s(device, &arg);
                    break;
                case 'u':
                    handle_u(device, &arg);
                    break;
                case 'x':{
                            int digits = 0;
                            int res = char_to_number(ascii_string[i+1]);
                            while(res != -1){
                                i++;
                                digits*=10;
                                digits+=res;
                                res = char_to_number(ascii_string[i+1]);
                            }
                            handle_x_or_X(device, &arg, 'x', digits);
                            break;
                         }
                case 'X':{
                            int digits = 0;
                            int res = char_to_number(ascii_string[i+1]);
                            while(res != -1){
                                i++;
                                digits*=10;
                                digits+=res;
                                res = char_to_number(ascii_string[i+1]);
                            }
                            handle_x_or_X(device, &arg, 'X', digits);
                            break;
                         }
                case 'p':{
                            int digits = 0;
                            int res = char_to_number(ascii_string[i+1]);
                            while(res != -1){
                                i++;
                                digits*=10;
                                digits+=res;
                                res = char_to_number(ascii_string[i+1]);
                            }
                            handle_p(device, &arg, digits);
                            break;
                         }
                case 'n':
                    handle_n(&arg);
                    break;
                case '%':
                    printc(device, '%');
                    break;
            }
        }
        else{
            printc(device, ascii_string[i]);
        }
    }
    va_end(arg);
    characters_printed = 0;
}


