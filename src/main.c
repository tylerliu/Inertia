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

#include "Instr_set.h"
#include "RegMem.h"
#include "Execution.h"


//Error type
#define IOException 0
#define AllocationException 1
#define ArrayOutOfBoundException 2

uint32_t *instr;

FILE *f;
uint32_t len_program;
uint32_t *program;

void on_error(int type) {
    switch (type) {
        case ArrayOutOfBoundException:
            printf("Instruction array out of bound\n");
            break;
        default:
            printf("Error Occurred\n");
            break;
    }
    fclose(f);
    free(program);
    exit(1);
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

void func(Instr_format_U *instr, uint32_t *pc, int *running){
    if ((instr->imm12_31) == 0){//call, have to follow with JAL/JALR
        (*pc) ++;
        run(*pc - 1);//start at JAL/JALR
    }
    if ((instr->imm12_31) == 1){//return
        (*running) = 0;
    }
    if ((instr->imm12_31) == 1){//realloc();
        memory = realloc(memory, (uint32_t)int_regs[instr->rd]);
    }
}

/* evaluate the last decoded instruction */
void eval(int *running, uint32_t *pc) {
    uint32_t temp;
    temp = fetch(pc);
    instr = &temp;
    //printf("NUM: %d\n", *instr);
    switch ((*instr) & 127) {
        case OP_IMM:
            op_imm((Instr_format_I *)instr);
            break;
        case OP:
            op((Instr_format_R *)instr);
            break;
        case LUI:
            lui((Instr_format_U *)instr);
            break;
        case AUIPC:
            auipc((Instr_format_U *)instr, pc);
            break;
        case JAL:
            jal((Instr_format_UJ *)instr, pc);
            break;
        case JALR:
            jalr((Instr_format_I *)instr,pc);
            break;
        case BRANCH:
            branch((Instr_format_SB *)instr, pc);
            break;
        case LOAD:
            load((Instr_format_I *)instr);
            break;
        case STORE:
            store((Instr_format_S *)instr);
            break;
        case IO:
            io((Instr_format_U *)instr);
            break;
        case FUNC:
            func((Instr_format_U *)instr, pc, running);
            break;
        case LOAD_FP:
            load_fp((Instr_format_I *)instr);
            break;
        case STORE_FP:
            store_fp((Instr_format_S *)instr);
            break;
        case OP_FP:
            op_fp((Instr_format_R4 *)instr);
            break;
        case FMADD:
            fmadd((Instr_format_R4 *)instr);
            break;
        case FMSUB:
            fmsub((Instr_format_R4 *)instr);
            break;
        case FNMADD:
            fnmadd((Instr_format_R4 *)instr);
            break;
        case FNMSUB:
            fnmsub((Instr_format_R4 *)instr);
            break;
        default:
            on_error(-1);
    }
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
    return 0;
}
