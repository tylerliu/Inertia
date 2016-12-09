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

int32_t int_regs[NUM_INT_REGS];//[0] is always 0
double fpt_regs[NUM_DOUBLE_REGS];

uint32_t len_mem;
void *memory;

//fcsr not defined
//pc defined in main program.

#endif /* RegMem.h */