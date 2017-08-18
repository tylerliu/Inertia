//
//  main.c
//  Inertia
//
//  Created by Tyler Liu on 2016/10/09.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//
// Byte code should be written in Little Endian.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "RegMem.h"
#include "Execution.h"


//Error type
#define Halt 0
#define IOException 1
#define AllocationException 2
#define ArrayOutOfBoundException 3

FILE *f;
//dictionary
const int length_op = 70;
void (*ops[length_op])(uint32_t *) = {addi, slti, sltui, andi, ori, xori, slli, srli, srai, muli, divi, divui, remi, remui,
                                 add, sub, slt, sltu, and, or, xor, sll, srl, sra, mul, division, divu, rem,
                                 remu, lui, auipc, jal, jalr, beq, bne, blt, bltu, bge, bgeu, lw, lh,
                                 lhu, lb, lbu, sw, sh, sb, flw, fld, fsw, fsd, fadd, fsub, fmul, fdiv,
                                 fsqrt, fcvt_d_w, fcvt_d_wu, fcvt_w_d, fcvt_wu_d, f_eq, f_lt, f_le, fmv, fneg, Fabs,
                                 scan, print, reallocation, Exit};
void on_error(int type) {
    switch (type) {
        case Halt:
            break;
        case ArrayOutOfBoundException:
            printf("Instruction array out of bound\n");
            break;
        default:
            printf("Error Occurred\n");
            break;
    }
    fclose(f);
    free(program);
    free(memory);
    exit(type);
}

uint32_t fetch() {
    //printf("fetch %d %u\n", pc, (program[pc]) & 0xFF);
    if (pc >= len_program) {
        on_error(ArrayOutOfBoundException);
    }
    pc++;
    return program[pc - 1];
}

/* evaluate the last decoded instruction */
void eval() {
    uint32_t instr = fetch();
    //printf("NUM: %d\n", instr);
    ops[(instr) & 0xFF](&instr);

}

int main( int argc, const char * argv[] )
{
    
    if (argc == 1) {
        printf("Please enter file name\n");
        on_error(IOException);
    }
    
    //read in file

    f = fopen(argv[1], "rb");
    //len_program = fgetu();

    if (fread(&len_program, 4, 1, f) != 1){
        printf("Error: %s\n", strerror(errno));
        on_error(IOException);
    }

    len_program ++; // extra space for exit

    program = (uint32_t *)malloc(len_program * sizeof(uint32_t));
    if(!program){
        on_error(AllocationException);
    }

    len_mem = 1 << 21;//alloc 2 MB mem space
    memory = malloc(len_mem);
    if(!memory){
        printf("Error: %s\n", strerror(errno));
        on_error(AllocationException);
    }

    if (fread(program, 4, len_program - 1, f) != (len_program - 1)) {
        printf("Error: %s\n", strerror(errno));
        on_error(IOException);
    }

    fclose(f);

    //pre-execution config
    pc = 0;
    running = 1;
    program[len_program - 1] = EXIT;
    int_regs[1] = len_program - 1;
    int_regs[2] = int_regs[3] = STACK_BEGIN;
    int_regs[4] = GLOBAL_PTR;
    //printf("len: %u\n", len_program);

    //execution
    while (running) {
        eval();
    }
    free(program);
    free(memory);
    return 0;
}
