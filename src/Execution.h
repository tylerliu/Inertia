//
//  Execution.h
//  Inertia
//
//  Created by Tyler Liu on 2016/12/03.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//
//  execution function

#ifndef _Execution_h
#define _Execution_h

#include "Instr_set.h"
#include "RegMem.h"

//for float NaN/Infinity/rounding mode
#include <math.h>
#include <fenv.h>

//RV32I/RV32M

void op_imm(Instr_format_I *); //Integer Register-Immediate Instructions, type I
void op(Instr_format_R *);     //Integer Register-Register Operations, type R
void lui(Instr_format_U *);    //load upper immediate, type U, load imm to dest.
void auipc(Instr_format_U *, uint32_t *);  //add upper immediate to pc, type U, add imm to pc, store in dest.
void jal(Instr_format_UJ *, uint32_t *);    //Unconditional jumps, type UJ, add immediate to pc.if dest = 0, plain jump. store pc+4 to rd after jump.
void jalr(Instr_format_I *, uint32_t *);   //jump and link register, type I, store pc+4 to rd after jump
void branch(Instr_format_SB *,uint32_t *); //branch statements, type SB, shift of offest.
void load(Instr_format_I *);   //load from memory, type I, The effective byte = s1 + IMM.
void store(Instr_format_S *);  //store to memory, type S, The effective byte = s1 + IMM.

//RV32F/RV32D
void load_fp(Instr_format_I *);   //load from memory, type I, The effective byte = s1 + IMM.
void store_fp(Instr_format_S *);  //store to memory, type S, The effective byte = s1 + IMM.
void op_fp(Instr_format_R4 *);
void fmadd(Instr_format_R4 *);
void fmsub(Instr_format_R4 *);
void fnmadd(Instr_format_R4 *);
void fnmsub(Instr_format_R4 *);

//IO
void io(Instr_format_U *);
void func(Instr_format_U *, uint32_t *, int *);
#endif /* Execution.h */