//
//  main.c
//  Inertia
//
//  Created by Tyler Liu on 2016/10/09.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//
// Byte code written in Little Endian.

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
uint32_t len_program;
uint32_t *program;
//dictionary
const int length_op = 69;
void (*ops[length_op])(uint32_t *, uint32_t *, int *) = {&addi, &slti, &sltui, &andi, &ori, &xori, &slli, &srli, &srai, &muli, &divi, &divui, &remi, & remui,
                                 &add, &sub, &slt, &sltu, &and, &or, &xor, &sll, &srl, &sra, &mul, &division, &divu, &rem,
                                 &remu, &lui, &jal, &jalr, &beq, &bne, &blt, &bltu, &bge, &bgeu, &lw, &lh,
                                 &lhu, &lb, &lbu, &sw, &sh, &sb, &flw, &fld, &fsw, &fsd, &fadd, &fsub, &fmul, &fdiv,
                                 &fsqrt, &fcvt_d_w, &fcvt_d_wu, &fcvt_w_d, &fcvt_wu_d, &f_eq, &f_lt, &f_le,
                                 &scan, &print, &call, &callr, &ret, &reallocation, &Exit};
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

uint32_t fetch(uint32_t *pc) {
    if (*pc >= len_program) {
        on_error(ArrayOutOfBoundException);
    }
    (*pc)++;
    //printf("fetch %d\n", *pc - 1);
    return program[*pc - 1];
}

void run(uint32_t pc);

/* evaluate the last decoded instruction */
void eval(int *running, uint32_t *pc) {
    uint32_t instr;
    instr = fetch(pc);
    //printf("NUM: %d\n", instr);
    ops[(instr) & 0xFF](&instr, pc, running);

}

// run with program counter
void run(uint32_t pc) {
    int running = 1;
    while (running) {
        eval(&running, &pc);
    }
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
    program = (uint32_t *)malloc(len_program * sizeof(uint32_t));
    if(!program){
        on_error(AllocationException);
    }

    if (fread(&len_mem, 4, 1, f) != 1){
        printf("Error: %s\n", strerror(errno));
        on_error(IOException);
    }
    memory = malloc(len_mem);
    if(!memory){
        printf("Error: %s\n", strerror(errno));
        on_error(AllocationException);
    }

    if (fread(program, 4, len_program, f) != len_program) {
        printf("Error: %s\n", strerror(errno));
        on_error(IOException);
    }

    fclose(f);

    //execute
    run(0);
    free(program);
    free(memory);
    return 0;
}
