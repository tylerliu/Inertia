//
//  RegMem.h
//  Inertia
//
//  Created by Tyler Liu on 2016/12/03.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//
//  Register and Memory model

#ifndef _RegMem_h
#define _RegMem_h
#include <stdint.h>

#define NUM_INT_REGS 32
#define NUM_DOUBLE_REGS 32
#define STACK_BEGIN 65535

//program counter
uint32_t pc;
uint32_t running;
/* reg[0] is always 0
 * reg[1] is return address
 * reg[2] is stack base pointer
 * reg[3] is stack top pointer
 * reg[4] is temporary register
 */
int32_t int_regs[NUM_INT_REGS];

double fpt_regs[NUM_DOUBLE_REGS];

uint32_t len_program;
uint32_t *program;


uint32_t len_mem;
void *memory;//first 65536 byte is stack.

//fcsr not defined
//pc defined in main program.

#endif /* RegMem.h */