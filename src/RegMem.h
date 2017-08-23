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
#define STACK_BEGIN 2097148
  // mem size = (1 << 21 - 4), 2MB

#define GLOBAL_PTR 8196
#define GLOBAL_START 4
  //(GLOBAL_PTR - (1 << 13))

//program counter
uint32_t pc;
uint32_t running;

/* reg[0] is always 0
 * reg[1] is return address
 * reg[2] is stack base pointer
 * reg[3] is stack top pointer
 * reg[4] is global area pointer
 * reg[5] is temporary register
 * reg 6-21 are argument register/return register
 */

int32_t int_regs[NUM_INT_REGS];

double fpt_regs[NUM_DOUBLE_REGS];

uint32_t len_program;
uint32_t *program;


uint32_t len_mem;
void *memory;

//fcsr not defined
//pc defined in main program.

#endif /* RegMem.h */