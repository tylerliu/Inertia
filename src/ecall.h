//
// Created by Tyler on 2017/08/23.
//

#ifndef ECALL_H
#define ECALL_H

#include <stdint.h>

void ecall_funct(uint8_t set, uint32_t func);

/*
 * call sets:
 * 0: essential system function
 * 1: standard IO handling
 */

/*
 * essential system function
 * 0: exit
 */
void Exit();

/*
 * standard IO handling
 * 0: print_char
 * 1: print_int
 * 2: print_double
 * 3: print_string
 * 4: read_char
 * 5: read_int
 * 6: read_double
 * 7: read_string
 */

void print_char();
void print_int();
void print_double(); 
void print_string(); 
void read_char(); 
void read_int(); 
void read_double(); 
void read_string();



#endif /* ecall.h */
