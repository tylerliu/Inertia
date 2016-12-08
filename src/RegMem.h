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

//TODO Dynamic Memory Allocation
#define NUM_INT_MEMS 65536
#define NUM_DOUBLE_MEMS 65536

#define getIntReg(a) int_regs[a]
#define setIntReg(a, val) if ((a) != 0) int_reg[a] = (val)

int32_t int_regs[NUM_INT_REGS];//[0] is always 0
double fpt_regs[NUM_DOUBLE_REGS];
int32_t int_memory[NUM_INT_MEMS];
double fpt_memory[NUM_DOUBLE_MEMS];

//fcsr not defined
//pc defined in main program.

#endif /* RegMem.h */