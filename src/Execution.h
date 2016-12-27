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

extern void run(uint32_t pc);
extern void on_error(int type);
//Integer Register-Immediate Instructions, type I
//OPIMM
void addi(uint32_t *instr, uint32_t *pc, int *running);
void slti(uint32_t *instr, uint32_t *pc, int *running);
void sltui(uint32_t *instr, uint32_t *pc, int *running);
void andi(uint32_t *instr, uint32_t *pc, int *running);
void ori(uint32_t *instr, uint32_t *pc, int *running);
void xori(uint32_t *instr, uint32_t *pc, int *running);
void slli(uint32_t *instr, uint32_t *pc, int *running);
void srli(uint32_t *instr, uint32_t *pc, int *running);
void srai(uint32_t *instr, uint32_t *pc, int *running);
void muli(uint32_t *instr, uint32_t *pc, int *running);
void divi(uint32_t *instr, uint32_t *pc, int *running);
void divui(uint32_t *instr, uint32_t *pc, int *running);
void remi(uint32_t *instr, uint32_t *pc, int *running);
void remui(uint32_t *instr, uint32_t *pc, int *running);

//Integer Register-Register Operations, type R
//OP
void add(uint32_t *instr, uint32_t *pc, int *running);
void sub(uint32_t *instr, uint32_t *pc, int *running);
void slt(uint32_t *instr, uint32_t *pc, int *running);
void sltu(uint32_t *instr, uint32_t *pc, int *running);
void and(uint32_t *instr, uint32_t *pc, int *running);
void or(uint32_t *instr, uint32_t *pc, int *running);
void xor(uint32_t *instr, uint32_t *pc, int *running);
void sll(uint32_t *instr, uint32_t *pc, int *running);
void srl(uint32_t *instr, uint32_t *pc, int *running);
void sra(uint32_t *instr, uint32_t *pc, int *running);
void mul(uint32_t *instr, uint32_t *pc, int *running);
void division(uint32_t *instr, uint32_t *pc, int *running);
void divu(uint32_t *instr, uint32_t *pc, int *running);
void rem(uint32_t *instr, uint32_t *pc, int *running);
void remu(uint32_t *instr, uint32_t *pc, int *running);

void lui(uint32_t *instr, uint32_t *pc, int *running); //load upper immediate, type U, load imm to dest.
void jal(uint32_t *instr, uint32_t *pc, int *running);    //Unconditional jumps, type UJ, add immediate to pc.if dest = 0, plain jump. store pc+4 to rd after jump.
void jalr(uint32_t *instr, uint32_t *pc, int *running);   //jump and link register, type I, store pc+4 to rd after jump

//branch statements, type SB, shift of offest.
//BRANCH
void beq(uint32_t *instr, uint32_t *pc, int *running);
void bne(uint32_t *instr, uint32_t *pc, int *running);
void blt(uint32_t *instr, uint32_t *pc, int *running);
void bltu(uint32_t *instr, uint32_t *pc, int *running);
void bge(uint32_t *instr, uint32_t *pc, int *running);
void bgeu(uint32_t *instr, uint32_t *pc, int *running);

//load from memory, type I, The effective byte = s1 + IMM.
//LOAD
void lw(uint32_t *instr, uint32_t *pc, int *running);
void lh(uint32_t *instr, uint32_t *pc, int *running);
void lhu(uint32_t *instr, uint32_t *pc, int *running);
void lb(uint32_t *instr, uint32_t *pc, int *running);
void lbu(uint32_t *instr, uint32_t *pc, int *running);

//store to memory, type S, The effective byte = s1 + IMM.
//STORE
void sw(uint32_t *instr, uint32_t *pc, int *running);
void sh(uint32_t *instr, uint32_t *pc, int *running);
void sb(uint32_t *instr, uint32_t *pc, int *running);

//RV32F/RV32D
//load from memory, type I, The effective byte = s1 + IMM.
//LOAD_FP
void flw(uint32_t *instr, uint32_t *pc, int *running);
void fld(uint32_t *instr, uint32_t *pc, int *running);

//store to memory, type S, The effective byte = s1 + IMM.
//STORE_FP
void fsw(uint32_t *instr, uint32_t *pc, int *running);
void fsd(uint32_t *instr, uint32_t *pc, int *running);

//OP_FP
void fadd(uint32_t *instr, uint32_t *pc, int *running);
void fsub(uint32_t *instr, uint32_t *pc, int *running);
void fmul(uint32_t *instr, uint32_t *pc, int *running);
void fdiv(uint32_t *instr, uint32_t *pc, int *running);
void fsqrt(uint32_t *instr, uint32_t *pc, int *running);
void fcvt_d_w(uint32_t *instr, uint32_t *pc, int *running);
void fcvt_d_wu(uint32_t *instr, uint32_t *pc, int *running);
void fcvt_w_d(uint32_t *instr, uint32_t *pc, int *running);
void fcvt_wu_d(uint32_t *instr, uint32_t *pc, int *running);
void f_eq(uint32_t *instr, uint32_t *pc, int *running);
void f_lt(uint32_t *instr, uint32_t *pc, int *running);
void f_le(uint32_t *instr, uint32_t *pc, int *running);

//IO
void scan(uint32_t *instr, uint32_t *pc, int *running);
void print(uint32_t *instr, uint32_t *pc, int *running);

void call(uint32_t *instr, uint32_t *pc, int *running);//in main.c
void callr(uint32_t *instr, uint32_t *pc, int *running);//in main.c
void ret(uint32_t *instr, uint32_t *pc, int *running);
void reallocation(uint32_t *instr, uint32_t *pc, int *running);
void Exit(uint32_t *instr, uint32_t *pc, int *running);

#endif /* Execution.h */