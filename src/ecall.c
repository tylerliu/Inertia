//
// Created by Tyler on 2017/08/23.
//

#include <stdio.h>
#include "ecall.h"
#include "RegMem.h"

#define num_set 2
#define num_func 10

void (*ecall_func[num_set][num_func])() = {
        {Exit},
        {print_char, print_int, print_double, print_string, read_char, read_int, read_double, read_string}
};

void ecall_funct(uint8_t set, uint32_t func){
    (ecall_func[set][func])();
}



void Exit(){
    running = 0;
}

void print_char(){
    putchar(int_regs[6]);
}

void print_int(){
    printf("%d", int_regs[6]);
}

void print_double(){
    printf("%lf", fpt_regs[1]);
}

void print_string(){
    printf("%s", (char *)(memory + int_regs[6]));
}

void read_char(){
    int_regs[6] = getchar();
}

void read_int(){
    scanf("%d", &int_regs[6]);
}

void read_double(){
    scanf("%lf", &fpt_regs[1]);
}

void read_string(){
    scanf("%s", (char *)(memory + int_regs[6]));
}
 
