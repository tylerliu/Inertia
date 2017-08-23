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

//Integer Register-Immediate Instructions, type I
//OPIMM
void addi(uint32_t *instr);
void slti(uint32_t *instr);
void sltui(uint32_t *instr);
void andi(uint32_t *instr);
void ori(uint32_t *instr);
void xori(uint32_t *instr);
void slli(uint32_t *instr);
void srli(uint32_t *instr);
void srai(uint32_t *instr);
void muli(uint32_t *instr);
void divi(uint32_t *instr);
void divui(uint32_t *instr);
void remi(uint32_t *instr);
void remui(uint32_t *instr);

//Integer Register-Register Operations, type R
//OP
void add(uint32_t *instr);
void sub(uint32_t *instr);
void slt(uint32_t *instr);
void sltu(uint32_t *instr);
void and(uint32_t *instr);
void or(uint32_t *instr);
void xor(uint32_t *instr);
void sll(uint32_t *instr);
void srl(uint32_t *instr);
void sra(uint32_t *instr);
void mul(uint32_t *instr);
void division(uint32_t *instr);
void divu(uint32_t *instr);
void rem(uint32_t *instr);
void remu(uint32_t *instr);

void lui(uint32_t *instr); //load upper immediate, type U, load imm to dest.
void auipc(uint32_t *instr);
void jal(uint32_t *instr);    //Unconditional jumps, type UJ, add immediate to pc.if dest = 0, plain jump. store pc+4 to rd after jump.
void jalr(uint32_t *instr);   //jump and link register, type I, store pc+4 to rd after jump

//branch statements, type SB, shift of offest.
//BRANCH
void beq(uint32_t *instr);
void bne(uint32_t *instr);
void blt(uint32_t *instr);
void bltu(uint32_t *instr);
void bge(uint32_t *instr);
void bgeu(uint32_t *instr);

//load from memory, type I, The effective byte = s1 + IMM.
//LOAD
void lw(uint32_t *instr);
void lh(uint32_t *instr);
void lhu(uint32_t *instr);
void lb(uint32_t *instr);
void lbu(uint32_t *instr);

//store to memory, type S, The effective byte = s1 + IMM.
//STORE
void sw(uint32_t *instr);
void sh(uint32_t *instr);
void sb(uint32_t *instr);

//RV32F/RV32D
//load from memory, type I, The effective byte = s1 + IMM.
//LOAD_FP
void flw(uint32_t *instr);
void fld(uint32_t *instr);

//store to memory, type S, The effective byte = s1 + IMM.
//STORE_FP
void fsw(uint32_t *instr);
void fsd(uint32_t *instr);

//OP_FP
void fadd(uint32_t *instr);
void fsub(uint32_t *instr);
void fmul(uint32_t *instr);
void fdiv(uint32_t *instr);
void fsqrt(uint32_t *instr);
void fcvt_d_w(uint32_t *instr);
void fcvt_d_wu(uint32_t *instr);
void fcvt_w_d(uint32_t *instr);
void fcvt_wu_d(uint32_t *instr);
void f_eq(uint32_t *instr);
void f_lt(uint32_t *instr);
void f_le(uint32_t *instr);

void fmv(uint32_t *instr);
void fneg(uint32_t *instr);
void Fabs(uint32_t *instr);

//environment call
void ecall(uint32_t *instr);
#endif /* Execution.h */