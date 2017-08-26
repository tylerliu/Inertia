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
 * 2: dynamic memory allocation
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
 * 8: open file
 * 9: close file
 * 10: flush file buffer
 * 11: rewind file, or reset current position to beginning
 * 12: fseek, let current position to certain location
 * 13: test for end of file
 * 14: test for error
 * 15: write bytes to file
 * 16: read bytes from file
 */
void io_init();
void io_free();

void print_char();
void print_int();
void print_double(); 
void print_string(); 
void read_char(); 
void read_int(); 
void read_double(); 
void read_string();
void file_open();
void file_close();
void file_flush();
void file_rewind();
void file_tell();
void file_seek();
void file_eof();
void file_error();
void file_write();
void file_read();

/*
 * dynamic memory allocation
 * 0: allocating new memory block
 * 1: freeing memory block
 * 2: reallocation memory block to a new size
 * 3: print the statistic of blocks in heap
 */

void mem_alloc();
void mem_free();
void mem_realloc();
void mem_print_stat();



#endif /* ecall.h */
