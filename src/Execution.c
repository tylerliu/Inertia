//
//  Execution.c
//  Inertia
//
//  Created by Tyler Liu on 2016/12/03.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//
//  execution function

#include "Execution.h"
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
    int_regs[instr->rd] = get_imm_U(instr);
}

//add upper immediate to pc, type U, add imm to pc, store in dest.
void auipc(Instr_format_U *instr, uint32_t *pc){
    //if (instr->rd == 0) return;
    int_regs[instr->rd] = (get_imm_U(instr) >> 2) + *pc;
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
            val = int_regs[instr->rs1] == int_regs[instr->rs2];
            break;
        case BNE:
            val = int_regs[instr->rs1] != int_regs[instr->rs2];
            break;
        case BLT:
            val = int_regs[instr->rs1] < int_regs[instr->rs2];
            break;
        case BLTU:
            val = ((uint32_t)int_regs[instr->rs1]) < ((uint32_t)int_regs[instr->rs2]);
            break;
        case BGE:
            val = int_regs[instr->rs1] > int_regs[instr->rs2];
            break;
        case BGEU:
            val = ((uint32_t)int_regs[instr->rs1]) > ((uint32_t)int_regs[instr->rs2]);
            break;
        default:
            val = 0;
            break;
    }
    if (!val) *pc = *pc + (get_imm_SB(instr) >> 2);
}

//load from int_memory, type I, The effective byte = s1 + IMM.
void load(Instr_format_I *instr){
    //if (instr->rd == 0) return;
    switch (instr->funct3){
        case LW:
            int_regs[instr->rd] = *(int32_t *)(memory+(int_regs[instr->rs1] + get_imm_I(instr)));
            break;
        case LH:
            int_regs[instr->rd] = *(int16_t *)(memory+(int_regs[instr->rs1] + get_imm_I(instr)));
            break;
        case LHU:
            int_regs[instr->rd] = *(uint16_t *)(memory+(int_regs[instr->rs1] + get_imm_I(instr)));
            break;
        case LB:
            int_regs[instr->rd] = *(int8_t *)(memory+(int_regs[instr->rs1] + get_imm_I(instr)));
            break;
        case LBU:
            int_regs[instr->rd] = *(uint8_t *)(memory+(int_regs[instr->rs1] + get_imm_I(instr)));
            break;
        default:
            break;
    }
}

//store to int_memory, type S, The effective byte = s1 + IMM.
void store(Instr_format_S *instr){
    switch (instr->funct3){
        case SW:
            *(int32_t *)(memory+(int_regs[instr->rs1] + get_imm_S(instr))) = int_regs[instr->rs2];
            break;
        case SH:
            *(int16_t *)(memory+(int_regs[instr->rs1] + get_imm_S(instr))) = (int16_t) (int_regs[instr->rs2] & 0xFFFF);
            break;
        case SB:
            *(int8_t *)(memory+(int_regs[instr->rs1] + get_imm_S(instr))) = (int8_t) (int_regs[instr->rs2] & 0xFF);
            break;
        default:
            break;
    }
}


//RV32F/RV32D

//load from int_memory, type I, The effective byte = s1 + IMM.
void load_fp(Instr_format_I *instr){
    switch(instr->funct3) {
        case DLE:
            fpt_regs[instr->rd] = *(double *)(memory+(int_regs[instr->rs1] + get_imm_I(instr)));
            break;
        case FLT:
            fpt_regs[instr->rd] = *(float *)(memory+(int_regs[instr->rs1] + get_imm_I(instr)));
            break;
        default:
            break;
    }
}

//store to int_memory, type S, The effective byte = s1 + IMM.
void store_fp(Instr_format_S *instr){
    switch(instr->funct3) {
        case DLE:
            *(double *)(memory+(int_regs[instr->rs1] + get_imm_S(instr))) = fpt_regs[instr->rs2];
            break;
        case FLT:
            *(float *)(memory+(int_regs[instr->rs1] + get_imm_S(instr))) = (float)fpt_regs[instr->rs2];
            break;
        default:
            break;
    }
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

    if ((in >> 1) & 1) {//print literals
        if ((in >> 2) & 0xFF) printf("%c", (in >> 2) & 0xFF);
        if ((in >> 10) & 0xFF) printf("%c", (in >> 10) & 0xFF);
        return;
    }

    switch ((in >> 17) & 7){//flag
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
    uint32_t i = (in >> 13) & 15;
    if (i > 0){
        sprintf(mk, "%u", i);
        strcat(fm, mk);
    }

    //precision, not doing if equal to 0
    i = (in >> 9) & 15;
    if (i > 0){
        sprintf(mk, ".%u", i);
        strcat(fm, mk);
    }

    //length
    switch ((in >> 6) & 7){
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
    switch ((in >> 2) & 15){
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
    if (in & 1){//output
        if (((in >> 2) & 15) >= 2 && ((in >> 2) & 15) <= 7){//fpt
            printf(fm, fpt_regs[instr->rd]);
        }
        else{//int
            printf(fm, int_regs[instr->rd]);
        }
    }
    else{//input
        if (((in >> 2) & 15) >= 2 && ((in >> 2) & 15) <= 7){//fpt
            scanf(fm, &(fpt_regs[instr->rd]));
        }
        else{//int
            scanf(fm, &(int_regs[instr->rd]));
        }
    }
}