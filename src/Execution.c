//
//  Execution.c
//  Inertia
//
//  Created by Tyler Liu on 2016/12/03.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//
//  execution function

#include "Execution.h"
#include "Instr_set.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INT_REG_OF(format,loc) int_regs[((Instr_format_##format *)instr)->loc]
#define FPT_REG_OF(format,loc) fpt_regs[((Instr_format_##format *)instr)->loc]
#define GET_IMM(format) get_imm_##format(((Instr_format_##format *)instr))

// Integer Register-Immediate Instructions, type I
void addi(uint32_t *instr){
    //printf("instr: 0x%08X, rd %u, rs1 %u, imm %d\n",*instr, ((Instr_format_I *)instr)->rd, ((Instr_format_I *)instr)->rs1, ((Instr_format_I *)instr)->imm);
    INT_REG_OF(I,rd) = INT_REG_OF(I,rs1) + GET_IMM(I);
    //int_regs[((Instr_format_I *)instr)->rd] = int_regs[((Instr_format_I *)instr)->rs1] + get_imm_I(((Instr_format_I *)instr));
}
void slti(uint32_t *instr){
    INT_REG_OF(I,rd) = INT_REG_OF(I,rs1) < GET_IMM(I);
    }
void sltui(uint32_t *instr){
    INT_REG_OF(I,rd) = (uint32_t)INT_REG_OF(I,rs1) < GET_IMM(I);
    }
void andi(uint32_t *instr){
    INT_REG_OF(I,rd) = INT_REG_OF(I,rs1) & GET_IMM(I);
    }
void ori(uint32_t *instr){
    INT_REG_OF(I,rd) = INT_REG_OF(I,rs1) | GET_IMM(I);
    }
void xori(uint32_t *instr){
    INT_REG_OF(I,rd) = INT_REG_OF(I,rs1) ^ GET_IMM(I);
    }
void slli(uint32_t *instr){
    INT_REG_OF(I,rd) = (INT_REG_OF(I,rs1) << (((Instr_format_I *)instr)->imm & 31));
    }
void srai(uint32_t *instr){
    INT_REG_OF(I,rd) = (INT_REG_OF(I,rs1) >> (((Instr_format_I *)instr)->imm & 31));//signed
}
void srli(uint32_t *instr){
    INT_REG_OF(I,rd) = (int32_t)((uint32_t)INT_REG_OF(I,rs1) >> (((Instr_format_I *)instr)->imm & 31));//unsigned
}
void muli(uint32_t *instr){
    INT_REG_OF(I,rd) = INT_REG_OF(I,rs1) * GET_IMM(I);
}
void divi(uint32_t *instr){
    INT_REG_OF(I,rd) = INT_REG_OF(I,rs1) / GET_IMM(I);
}
void divui(uint32_t *instr){
    INT_REG_OF(I,rd) = (int32_t)((uint32_t)INT_REG_OF(I,rs1) / ((Instr_format_I *)instr)->imm);
}
void remi(uint32_t *instr){
    INT_REG_OF(I,rd) = INT_REG_OF(I,rs1) % GET_IMM(I);
}
void remui(uint32_t *instr){
    INT_REG_OF(I,rd) = (int32_t)((uint32_t)INT_REG_OF(I,rs1) % ((Instr_format_I *)instr)->imm);
}

//Integer Register-Register Operations, type R
void add(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) + INT_REG_OF(R,rs2);
}
void sub(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) - INT_REG_OF(R,rs2);
}
void slt(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) < INT_REG_OF(R,rs2);
}
void sltu(uint32_t *instr){
    INT_REG_OF(R,rd) = (uint32_t) INT_REG_OF(R,rs1) < INT_REG_OF(R,rs2);
}
void and(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) & INT_REG_OF(R,rs2);
}
void or(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) | INT_REG_OF(R,rs2);
}
void xor(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) ^ INT_REG_OF(R,rs2);
    }
void sll(uint32_t *instr){
    INT_REG_OF(R,rd) = (INT_REG_OF(R,rs1) << (INT_REG_OF(R,rs2) & 31));
    }
void sra(uint32_t *instr){
        INT_REG_OF(R,rd) = (INT_REG_OF(R,rs1) >> (INT_REG_OF(R,rs2) & 31));
    }
void srl(uint32_t *instr){
        INT_REG_OF(R,rd) = (int32_t) ((uint32_t) INT_REG_OF(R,rs1) >> (INT_REG_OF(R,rs2) & 31));
    }
void mul(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) * INT_REG_OF(R,rs2);
    }
void division(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) / INT_REG_OF(R,rs2);
    }
void divu(uint32_t *instr){
    INT_REG_OF(R,rd) = (int32_t)((uint32_t)INT_REG_OF(R,rs1) / (uint32_t)INT_REG_OF(R,rs2));
    }
void rem(uint32_t *instr){
    INT_REG_OF(R,rd) = INT_REG_OF(R,rs1) % INT_REG_OF(R,rs2);
    }
void remu(uint32_t *instr){
    INT_REG_OF(R,rd) = (int32_t)((uint32_t)INT_REG_OF(R,rs1) % (uint32_t)INT_REG_OF(R,rs2));
    }

//load upper immediate, type U, load imm to dest.
void lui(uint32_t *instr){
    INT_REG_OF(U,rd) = GET_IMM(U);
}

//add upper immediate to pc, type U, load imm + pc to dest.
void auipc(uint32_t *instr){
    INT_REG_OF(U,rd) = pc + GET_IMM(U);
}

//Unconditional jumps, type UJ, add immediate to pc.if dest = 0, plain jump. store pc+1 to dest after jump.(next instr)
void jal(uint32_t *instr){
    if (((Instr_format_U *)instr)->rd != 0) INT_REG_OF(U,rd) = pc;
    pc = pc + get_imm_UJ(((Instr_format_U *)instr));
}

//jump and link register, type I, store pc+4 to dest after jump.(next instr)
void jalr(uint32_t *instr){
    if (((Instr_format_I *)instr)->rd != 0) INT_REG_OF(I,rd) = pc;
    pc = (uint32_t)((uint32_t)INT_REG_OF(I,rs1) + GET_IMM(I));
}

//branch statements, type SB, shift of offest.
void beq(uint32_t *instr){
    if (INT_REG_OF(S,rs1) == INT_REG_OF(S,rs2)) pc = pc + GET_IMM(S);
}
void bne(uint32_t *instr){
    if (INT_REG_OF(S,rs1) != INT_REG_OF(S,rs2)) pc = pc + GET_IMM(S);
}
void blt(uint32_t *instr){
    if (INT_REG_OF(S,rs1) < INT_REG_OF(S,rs2)) pc = pc + GET_IMM(S);
}
void bltu(uint32_t *instr){
    if (((uint32_t)INT_REG_OF(S,rs1)) < ((uint32_t)INT_REG_OF(S,rs2))) pc = pc + GET_IMM(S);
}
void bge(uint32_t *instr){
    if (INT_REG_OF(S,rs1) > INT_REG_OF(S,rs2)) pc = pc + GET_IMM(S);
}
void bgeu(uint32_t *instr){
    if (((uint32_t)INT_REG_OF(S,rs1)) > ((uint32_t)INT_REG_OF(S,rs2))) pc = pc + GET_IMM(S);
}

//load from int_memory, type I, The effective byte = s1 + IMM.
void lw(uint32_t *instr){
    //printf("instr: 0x%08X, rd%u, rs1%u, imm%u\n",*instr, ((Instr_format_I *)instr)->rd, ((Instr_format_I *)instr)->rs1, ((Instr_format_I *)instr)->imm);
    INT_REG_OF(I,rd) = *(int32_t *)(memory+(INT_REG_OF(I,rs1) + GET_IMM(I)));
    /*printf("Load: index %u, value %u, rs1 %u, from %u, was %u\n", ((Instr_format_I *)instr)->rd, INT_REG_OF(I,rd),
           ((Instr_format_I *)instr)->rs1, (INT_REG_OF(I,rs1) + GET_IMM(I)), *(int32_t *)(memory+(INT_REG_OF(I,rs1) + GET_IMM(I))));
           */
}
void lh(uint32_t *instr){
    INT_REG_OF(I,rd) = *(int16_t *)(memory+(INT_REG_OF(I,rs1) + GET_IMM(I)));
}
void lhu(uint32_t *instr){
    INT_REG_OF(I,rd) = *(uint16_t *)(memory+(INT_REG_OF(I,rs1) + GET_IMM(I)));
}
void lb(uint32_t *instr){
    INT_REG_OF(I,rd) = *(int8_t *)(memory+(INT_REG_OF(I,rs1) + GET_IMM(I)));
}
void lbu(uint32_t *instr){
    INT_REG_OF(I,rd) = *(uint8_t *)(memory+(INT_REG_OF(I,rs1) + GET_IMM(I)));
}


//store to memory, type S, The effective byte = s1 + IMM.
void sw(uint32_t *instr){
    *(int32_t *)(memory + (INT_REG_OF(S,rs1) + GET_IMM(S))) = INT_REG_OF(S,rs2);
    /*printf("Store: index %u, value %u, to %u, place %u\n", ((Instr_format_S *)instr)->rs2, INT_REG_OF(S,rs2),
           (INT_REG_OF(S,rs1) + GET_IMM(S)), *(int32_t *)(memory + (INT_REG_OF(S,rs1) + GET_IMM(S))));
           */
}
void sh(uint32_t *instr){
    *(int16_t *)(memory + (INT_REG_OF(S,rs1) + GET_IMM(S))) = (int16_t) (INT_REG_OF(S,rs2));
}
void sb(uint32_t *instr){
    *(int8_t *) (memory + (INT_REG_OF(S,rs1) + GET_IMM(S))) = (int8_t)  (INT_REG_OF(S,rs2));
}

//load from memory, type I, The effective byte = s1 + IMM.
void fld(uint32_t *instr){
    FPT_REG_OF(I,rd) = *(double *)(memory+(INT_REG_OF(I,rs1) + GET_IMM(I)));
}
void flw(uint32_t *instr){
    FPT_REG_OF(I,rd) = *(float *)(memory+(INT_REG_OF(I,rs1) + GET_IMM(I)));
}

//store to memory, type S, The effective byte = s1 + IMM.
void fsd(uint32_t *instr){
    *(double *)(memory+(INT_REG_OF(S,rs1) + GET_IMM(S))) = FPT_REG_OF(S,rs2);
}
void fsw(uint32_t *instr){
    *(float *)(memory+(INT_REG_OF(S,rs1) + GET_IMM(S))) = (float)FPT_REG_OF(S,rs2);
}

//floating point operation.
void fadd(uint32_t *instr){
    FPT_REG_OF(R,rd) = FPT_REG_OF(R,rs1) + FPT_REG_OF(R,rs2);
}
void fsub(uint32_t *instr){
    FPT_REG_OF(R,rd) = FPT_REG_OF(R,rs1) - FPT_REG_OF(R,rs2);
}
void fmul(uint32_t *instr){
    FPT_REG_OF(R,rd) = FPT_REG_OF(R,rs1) * FPT_REG_OF(R,rs2);
}
void fdiv(uint32_t *instr){
    FPT_REG_OF(R,rd) = FPT_REG_OF(R,rs1) / FPT_REG_OF(R,rs2);
}
void fsqrt(uint32_t *instr){
    FPT_REG_OF(R,rd) = sqrt(FPT_REG_OF(R,rs1));
}
void fcvt_d_wu(uint32_t *instr){
    INT_REG_OF(R,rd) = (int32_t)((uint32_t)FPT_REG_OF(R,rs1));
}
void fcvt_d_w(uint32_t *instr){
    INT_REG_OF(R,rd) = (int32_t)FPT_REG_OF(R,rs1);
}
void fcvt_wu_d(uint32_t *instr){
    FPT_REG_OF(R,rd) = (uint32_t)INT_REG_OF(R,rs1);
}
void fcvt_w_d(uint32_t *instr){
    FPT_REG_OF(R,rd) = INT_REG_OF(R,rs1);
}
void f_eq(uint32_t *instr){
    INT_REG_OF(R,rd) = FPT_REG_OF(R,rs1) == FPT_REG_OF(R,rs2);
}
void f_lt(uint32_t *instr){
    INT_REG_OF(R,rd) = FPT_REG_OF(R,rs1) < FPT_REG_OF(R,rs2);
}
void f_le(uint32_t *instr){
    INT_REG_OF(R,rd) = FPT_REG_OF(R,rs1) <= FPT_REG_OF(R,rs2);
}

void fmv(uint32_t *instr){
    FPT_REG_OF(R,rd) = FPT_REG_OF(R,rs1);
}

void fneg(uint32_t *instr){
    FPT_REG_OF(R,rd) = -FPT_REG_OF(R,rs1);
}

void Fabs(uint32_t *instr){
    FPT_REG_OF(R,rd) = fabs(FPT_REG_OF(R,rs1));
}

void scan(uint32_t *instr){
    //decode
    uint32_t in = ((Instr_format_U *)instr)->imm;
    char fm[11] = "%";
    char mk[4] = "";

    if (in & 1) {//print literals
        if ((in >> 2) & 0xFF) printf("%c", (in >> 2) & 0xFF);
        if ((in >> 10) & 0xFF) printf("%c", (in >> 10) & 0xFF);
        return;
    }

    switch ((in >> 16) & 7){//flag
        case 0://no flag
            break;
        case 1://-
            strcat(fm, "-");
            break;
        case 2://+
            strcat(fm, "+");
            break;
        case 3://" "
            strcat(fm, " ");
            break;
        case 4://0
            strcat(fm, "0");
            break;
        case 5://#
            strcat(fm, "#");
            break;
        default:
            break;
    }

    //field width, not doing if equal to 0
    uint32_t i = (in >> 12) & 15;
    if (i > 0){
        sprintf(mk, "%u", i);
        strcat(fm, mk);
    }

    //precision, not doing if equal to 0
    i = (in >> 8) & 15;
    if (i > 0){
        sprintf(mk, ".%u", i);
        strcat(fm, mk);
    }

    //length
    switch ((in >> 5) & 7){
        case 0:
            break;
        case 1:
            strcat(fm, "hh");
            break;
        case 2:
            strcat(fm, "h");
            break;
        case 3:
            strcat(fm, "l");
            break;
        case 4:
            strcat(fm, "ll");
            break;
        case 5:
            strcat(fm, "L");
            break;
        default:
            break;
    }

    //type
    switch ((in >> 1) & 15){
        case 0://"d"
            strcat(fm, "d");
            break;
        case 1://"u"
            strcat(fm, "u");
            break;
        case 2://"f"
            strcat(fm, "f");
            break;
        case 3://"F"
            strcat(fm, "F");
            break;
        case 4://"e"
            strcat(fm, "e");
            break;
        case 5://"E"
            strcat(fm, "E");
            break;
        case 6://"g"
            strcat(fm, "g");
            break;
        case 7://"G"
            strcat(fm, "G");
            break;
        case 8://"x"
            strcat(fm, "x");
            break;
        case 9://"X"
            strcat(fm, "X");
            break;
        case 10://"o"
            strcat(fm, "o");
            break;
        case 11://"c"
            strcat(fm, "c");
            break;
        case 12://"a"
            strcat(fm, "a");
            break;
        case 13://"A"
            strcat(fm, "A");
            break;
        case 14://"i"
            strcat(fm, "i");
            break;
        default:
            break;
    }
    if (((in >> 2) & 15) >= 2 && ((in >> 2) & 15) <= 7){//fpt
        scanf(fm, &(FPT_REG_OF(U,rd)));
    }
    else{//int
        scanf(fm, &(INT_REG_OF(U,rd)));
    }
}

void print(uint32_t *instr){
    //decode
    uint32_t in = ((Instr_format_U *)instr)->imm;
    char fm[11] = "%";
    char mk[4] = "";

    if (in & 1) {//print literals
        if ((in >> 2) & 0xFF) printf("%c", (in >> 2) & 0xFF);
        if ((in >> 10) & 0xFF) printf("%c", (in >> 10) & 0xFF);
        return;
    }

    switch ((in >> 16) & 7){//flag
        case 0://no flag
            break;
        case 1://-
            strcat(fm, "-");
            break;
        case 2://+
            strcat(fm, "+");
            break;
        case 3://" "
            strcat(fm, " ");
            break;
        case 4://0
            strcat(fm, "0");
            break;
        case 5://#
            strcat(fm, "#");
            break;
        default:
            break;
    }

    //field width, not doing if equal to 0
    uint32_t i = (in >> 12) & 15;
    if (i > 0){
        sprintf(mk, "%u", i);
        strcat(fm, mk);
    }

    //precision, not doing if equal to 0
    i = (in >> 8) & 15;
    if (i > 0){
        sprintf(mk, ".%u", i);
        strcat(fm, mk);
    }

    //length
    switch ((in >> 5) & 7){
        case 0:
            break;
        case 1:
            strcat(fm, "hh");
            break;
        case 2:
            strcat(fm, "h");
            break;
        case 3:
            strcat(fm, "l");
            break;
        case 4:
            strcat(fm, "ll");
            break;
        case 5:
            strcat(fm, "L");
            break;
        default:
            break;
    }

    //type
    switch ((in >> 1) & 15){
        case 0://"d"
            strcat(fm, "d");
            break;
        case 1://"u"
            strcat(fm, "u");
            break;
        case 2://"f"
            strcat(fm, "f");
            break;
        case 3://"F"
            strcat(fm, "F");
            break;
        case 4://"e"
            strcat(fm, "e");
            break;
        case 5://"E"
            strcat(fm, "E");
            break;
        case 6://"g"
            strcat(fm, "g");
            break;
        case 7://"G"
            strcat(fm, "G");
            break;
        case 8://"x"
            strcat(fm, "x");
            break;
        case 9://"X"
            strcat(fm, "X");
            break;
        case 10://"o"
            strcat(fm, "o");
            break;
        case 11://"c"
            strcat(fm, "c");
            break;
        case 12://"a"
            strcat(fm, "a");
            break;
        case 13://"A"
            strcat(fm, "A");
            break;
        case 14://"i"
            strcat(fm, "i");
            break;
        default:
            break;
    }

    //printf("%s", fm);
    if (((in >> 2) & 15) >= 2 && ((in >> 2) & 15) <= 7){//fpt
        printf(fm, FPT_REG_OF(U,rd));
    }
    else{//int
        printf(fm, INT_REG_OF(U,rd));
    }
}

void reallocation(uint32_t *instr){
    memory = realloc(memory, (uint32_t)INT_REG_OF(U,rd));
}

void Exit(uint32_t *instr){
    running = 0;
}
