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

// Integer Register-Immediate Instructions, type I
void op_imm(Instr_format_I * instr){
    //if (instr->rd == 0) return;
    switch(instr->funct3){
        case ADD:
            int_regs[instr->rd] = int_regs[instr->rs1] + get_imm_I(instr);
            break;
        case SLT:
            int_regs[instr->rd] = int_regs[instr->rs1] < get_imm_I(instr);
            break;
        case SLTU:
            int_regs[instr->rd] = (uint32_t)int_regs[instr->rs1] < get_imm_I(instr);
            break;
        case AND:
            int_regs[instr->rd] = int_regs[instr->rs1] & get_imm_I(instr);
            break;
        case OR:
            int_regs[instr->rd] = int_regs[instr->rs1] | get_imm_I(instr);
            break;
        case XOR:
            int_regs[instr->rd] = int_regs[instr->rs1] ^ get_imm_I(instr);
            break;
        case SLL:
            int_regs[instr->rd] = (int_regs[instr->rs1] << (instr->imm0_11 & 31));
            break;
        case SRL:
            if (((instr->imm0_11)>> 10) == 0b01) {//SRA?
                int_regs[instr->rd] = (int_regs[instr->rs1] >> (instr->imm0_11 & 31));//signed
            }
            else {
                int_regs[instr->rd] = (int32_t)((uint32_t)int_regs[instr->rs1] >> (instr->imm0_11 & 31));//unsigned
            }
            break;
        default:
            break;
    }
}

//Integer Register-Register Operations, type R
void op(Instr_format_R *instr) {
    //if (instr->rd == 0) return;
    if ((instr->funct7) != 0b0000001) {
        switch (instr->funct3) {
            case ADD://add/sub
                if (((instr->funct7) >> 5) == 0b01) {//sub
                    int_regs[instr->rd] = int_regs[instr->rs1] - int_regs[instr->rs2];
                } else {
                    int_regs[instr->rd] = int_regs[instr->rs1] + int_regs[instr->rs2];
                }
                break;
            case SLT:
                int_regs[instr->rd] = int_regs[instr->rs1] < int_regs[instr->rs2];
                break;
            case SLTU:
                int_regs[instr->rd] = (uint32_t) int_regs[instr->rs1] < int_regs[instr->rs2];
                break;
            case AND:
                int_regs[instr->rd] = int_regs[instr->rs1] & int_regs[instr->rs2];
                break;
            case OR:
                int_regs[instr->rd] = int_regs[instr->rs1] | int_regs[instr->rs2];
                break;
            case XOR:
                int_regs[instr->rd] = int_regs[instr->rs1] ^ int_regs[instr->rs2];
                break;
            case SLL:
                int_regs[instr->rd] = (int_regs[instr->rs1] << (int_regs[instr->rs2] & 31));
                break;
            case SRL:
                if (((instr->funct7) >> 5) == 0b01) {//SRA?
                    int_regs[instr->rd] = (int_regs[instr->rs1] >> (int_regs[instr->rs2] & 31));//signed
                } else {
                    int_regs[instr->rd] = (int32_t) ((uint32_t) int_regs[instr->rs1]
                            >> (int_regs[instr->rs2] & 31));//unsigned
                }
                break;
            default:
                break;
        }
    }
    else{
        switch (instr->funct3){
            case MUL:
                int_regs[instr->rd] = int_regs[instr->rs1] * int_regs[instr->rs2];
                break;
            case MULH:
                int_regs[instr->rd] = (int32_t)(((int64_t)int_regs[instr->rs1] * (int64_t)int_regs[instr->rs2]) >> 32);
                break;
            case MULHSU:
                int_regs[instr->rd] = (int32_t)(((int64_t)int_regs[instr->rs1] * (uint64_t)int_regs[instr->rs2]) >> 32);
                break;
            case MULHU:
                int_regs[instr->rd] = (int32_t)(((uint64_t)int_regs[instr->rs1] * (uint64_t)int_regs[instr->rs2]) >> 32);
                break;
            case DIV:
                int_regs[instr->rd] = int_regs[instr->rs1] / int_regs[instr->rs2];
                break;
            case DIVU:
                int_regs[instr->rd] = (int32_t)((uint32_t)int_regs[instr->rs1] / (uint32_t)int_regs[instr->rs2]);
                break;
            case REM:
                int_regs[instr->rd] = int_regs[instr->rs1] % int_regs[instr->rs2];
                break;
            case REMU:
                int_regs[instr->rd] = (int32_t)((uint32_t)int_regs[instr->rs1] % (uint32_t)int_regs[instr->rs2]);
                break;
            default:
                break;
        }
    }
}

//load upper immediate, type U, load imm to dest.
void lui(Instr_format_U *instr){
    //if (instr->rd == 0) return;
    int_regs[instr->rd] = instr->imm12_31;
}

//add upper immediate to pc, type U, add imm to pc, store in dest.
void auipc(Instr_format_U *instr, uint32_t *pc){
    //if (instr->rd == 0) return;
    int_regs[instr->rd] = (instr->imm12_31 >> 2) + *pc;
}

//Unconditional jumps, type UJ, add immediate to pc.if dest = 0, plain jump. store pc+4 to dest after jump.
void jal(Instr_format_UJ *instr, uint32_t *pc){
    *pc = *pc + (get_imm_UJ(instr) >> 2);
    if (instr->rd != 0) int_regs[instr->rd] = *pc + 1;
}

//jump and link register, type I, store pc+4 to dest after jump.
void jalr(Instr_format_I *instr, uint32_t *pc){
    *pc = *pc + ((instr->rs1 + get_imm_I(instr)) >> 2);
    if (instr->rd != 0) int_regs[instr->rd] = *pc + 1;
}

//branch statements, type SB, shift of offest.
void branch(Instr_format_SB *instr, uint32_t *pc){
    int val;
    switch (instr->funct3){
        case BEQ:
            val = instr->rs1 == instr->rs2;
            break;
        case BNE:
            val = instr->rs1 != instr->rs2;
            break;
        case BLT:
            val = instr->rs1 < instr->rs2;
            break;
        case BLTU:
            val = ((uint32_t)instr->rs1) < ((uint32_t)instr->rs2);
            break;
        case BGE:
            val = instr->rs1 > instr->rs2;
            break;
        case BGEU:
            val = ((uint32_t)instr->rs1) > ((uint32_t)instr->rs2);
            break;
        default:
            break;
    }
    if (!val) *pc = *pc + (get_imm_SB(instr) >> 2);
}

//load from int_memory, type I, The effective byte = s1 + IMM.
void load(Instr_format_I *instr){
    //if (instr->rd == 0) return;
    switch (instr->funct3){
        case LW:
            int_regs[instr->rd] = int_memory[int_regs[instr->rs1] + get_imm_I(instr)];
            break;
        case LH:
            if ((int_memory[int_regs[instr->rs1] + get_imm_I(instr)] >> 15) & 1) int_regs[instr->rd] = -1;
            int_regs[instr->rd] = (int_regs[instr->rd] << 16) + (int_memory[int_regs[instr->rs1] + get_imm_I(instr)] & 0xFFFF);
            break;
        case LHU:
            int_regs[instr->rd] = int_memory[int_regs[instr->rs1] + get_imm_I(instr)] & 0xFFFF;
            break;
        case LB:
            if ((int_memory[int_regs[instr->rs1] + get_imm_I(instr)] >> 7) & 1) int_regs[instr->rd] = -1;
            int_regs[instr->rd] = (int_regs[instr->rd] << 8) + (int_memory[int_regs[instr->rs1] + get_imm_I(instr)] & 0xFF);
            break;
        case LBU:
            int_regs[instr->rd] = int_memory[int_regs[instr->rs1] + get_imm_I(instr)] & 0xFF;
            break;
        default:
            break;
    }
}

//store to int_memory, type S, The effective byte = s1 + IMM.
void store(Instr_format_S *instr){
    switch (instr->funct3){
        case SW:
            int_memory[int_regs[instr->rs1] + get_imm_I(instr)] = int_regs[instr->rs2];
            break;
        case SH:
            int_memory[int_regs[instr->rs1] + get_imm_I(instr)] = int_regs[instr->rs2] & 0xFFFF;
            break;
        case SB:
            int_memory[int_regs[instr->rs1] + get_imm_I(instr)] = int_regs[instr->rs2] & 0xFF;
            break;
        default:
            break;
    }
}


//RV32F/RV32D

//load from int_memory, type I, The effective byte = s1 + IMM.
void load_fp(Instr_format_I *instr){
    //case DLE:
    //case FLT:
    fpt_regs[instr->rd] = fpt_memory[int_regs[instr->rs1] + get_imm_I(instr)];
}

//store to int_memory, type S, The effective byte = s1 + IMM.
void store_fp(Instr_format_S *instr){
    //case DLE:
    //case FLT:
    fpt_memory[int_regs[instr->rs1] + get_imm_I(instr)] = fpt_regs[instr->rs2];
}

void op_fp(Instr_format_R4 *instr){

    switch(instr->rs3){
        case FADD:
            fpt_regs[instr->rd] = fpt_regs[instr->rs1] + fpt_regs[instr->rs2];
            break;
        case FSUB:
            fpt_regs[instr->rd] = fpt_regs[instr->rs1] - fpt_regs[instr->rs2];
            break;
        case FMUL:
            fpt_regs[instr->rd] = fpt_regs[instr->rs1] * fpt_regs[instr->rs2];
            break;
        case FDIV:
            fpt_regs[instr->rd] = fpt_regs[instr->rs1] / fpt_regs[instr->rs2];
            break;
        case FSQRT:
            fpt_regs[instr->rd] = sqrt(fpt_regs[instr->rs1]);
            break;
        case FCVT_fmt_int:
            if (instr->rs2) {
                int_regs[instr->rd] = (int32_t)((uint32_t)fpt_regs[instr->rs1]);
            }else{
                int_regs[instr->rd] = (int32_t)fpt_regs[instr->rs1];
            }
            break;
        case FCVT_int_fmt:
            if (instr->rs2) {
                fpt_regs[instr->rd] = (uint32_t)fpt_regs[instr->rs1];
            }else{
                fpt_regs[instr->rd] = int_regs[instr->rs1];
            }
            break;
        case FCMP:
            switch (instr->funct3){
                case F_EQ:
                    int_regs[instr->rd] = fpt_regs[instr->rs1] == fpt_regs[instr->rs2];
                    break;
                case F_LT:
                    int_regs[instr->rd] = fpt_regs[instr->rs1] < fpt_regs[instr->rs2];
                    break;
                case F_LE:
                    int_regs[instr->rd] = fpt_regs[instr->rs1] <= fpt_regs[instr->rs2];
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

//rs1 * rs2 + rs3, type R4
void fmadd(Instr_format_R4 *instr){
    fpt_regs[instr->rd] = fpt_regs[instr->rs1] * fpt_regs[instr->rs2] + fpt_regs[instr->rs3];
}

//rs1 * rs2 - rs3, type R4
void fmsub(Instr_format_R4 *instr){
    fpt_regs[instr->rd] = fpt_regs[instr->rs1] * fpt_regs[instr->rs2] - fpt_regs[instr->rs3];
}

//-(rs1 * rs2 + rs3), type R4
void fnmadd(Instr_format_R4 *instr){
    fpt_regs[instr->rd] = -(fpt_regs[instr->rs1] * fpt_regs[instr->rs2] + fpt_regs[instr->rs3]);
}

//-(rs1 * rs2 - rs3), type R4
void fnmsub(Instr_format_R4 *instr){
    fpt_regs[instr->rd] = -(fpt_regs[instr->rs1] * fpt_regs[instr->rs2] - fpt_regs[instr->rs3]);
}

void io(Instr_format_U *instr){
    //decode
    uint32_t in = instr->imm12_31;
    char fm[11] = "%";
    char mk[4] = "";

    if((in >> 19) & 1)strcat(fm, "\n");//preceding new line
    if((in >> 18) & 1)strcat(fm, " ");//preceding space

    switch ((in >> 13) & 7){//flag
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

    //length, not doing if equal to 0
    uint32_t i = (in >> 9) & 15;
    if (i > 0){
        sprintf(mk, "%u", i);
        strcat(fm, mk);
    }

    //precision, not doing if equal to 0
    i = (in >> 5) & 15;
    if (i > 0){
        sprintf(mk, ".%u", i);
        strcat(fm, mk);
    }

    //type
    switch ((in >> 1) & 15){
        case 0://"d"
            strcat(fm, "d");
            break;
        case 1://"hd"
            strcat(fm, "hd");
            break;
        case 2://"u"
            strcat(fm, "u");
            break;
        case 3://"lf"
            strcat(fm, "lf");
            break;
        case 4://"Lf", not defined
            strcat(fm, "Lf");
            break;
        case 5://"le"
            strcat(fm, "le");
            break;
        case 6://"Le", not defined
            strcat(fm, "Le");
            break;
        case 7://"lg"
            strcat(fm, "lg");
            break;
        case 8://"Lg", not defined
            strcat(fm, "Lg");
            break;
        case 9://"x"
            strcat(fm, "x");
            break;
        case 10://"X"
            strcat(fm, "X");
            break;
        case 11://"o"
            strcat(fm, "o");
            break;
        case 12://"c"
            strcat(fm, "c");
            break;
        case 13://"a"
            strcat(fm, "a");
            break;
        case 14://"A"
            strcat(fm, "A");
            break;
        case 15://"i"
            strcat(fm, "i");
            break;
        default:
            break;
    }

    if((in >> 17) & 1)strcat(fm, " ");//succeeding space
    if((in >> 16) & 1)strcat(fm, "\n");//succeeding new line

    //printf("%s", fm);
    if (in & 1){//output
        if (((in >> 1) & 15) >= 3 && ((in >> 1) & 15) <= 8){//fpt
            printf(fm, fpt_regs[instr->rd]);
        }
        else{//int
            printf(fm, int_regs[instr->rd]);
        }
    }
    else{//input
        if (((in >> 1) & 15) >= 3 && ((in >> 1) & 15) <= 8){//fpt
            scanf(fm, &fpt_regs[instr->rd]);
        }
        else{//int
            scanf(fm, &int_regs[instr->rd]);
        }
    }
}