//
//  Instr_set.c
//  Inertia
//
//  Created by Tyler Liu on 2016/12/03.
//  Copyright © 2016 Tyler Liu. All rights reserved.

#include "Instr_set.h"
//parse instructions


//get immediate value
int32_t get_imm_I(Instr_format_I *instr){
    int32_t temp = 0;
    if ((*(int32_t *)instr) >> 31) temp = -1;
    temp = (temp << 12) + instr->imm0_11;//20-31
    return temp;
}

int32_t get_imm_S(Instr_format_S *instr){
    int32_t temp = 0;
    if ((*(int32_t *)instr) >> 31) temp = -1;
    temp = (temp << 7) + instr->imm5_11;//25-31
    temp = (temp << 5) + instr->imm0_4;//7-11
    return temp;
}

int32_t get_imm_SB(Instr_format_SB *instr){
    int32_t temp = 0;
    if (instr->imm12) temp = -1;
    temp = (temp << 1) + instr->imm11;
    temp = (temp << 7) + instr->imm5_10;//25-30
    temp = ((temp << 4) + instr->imm1_4) << 1;//8-11
    return temp;
}

int32_t get_imm_U(Instr_format_U *instr){
    int32_t temp = instr->imm12_31 << 12;//12-31
    return temp;
}

int32_t get_imm_UJ(Instr_format_UJ *instr){
    int32_t temp = 0;
    if (instr->imm20) temp = -1;
    temp = (temp << 8) + instr->imm12_19;
    temp = (temp << 1) + instr->imm11;
    temp = ((temp << 9) + instr->imm1_10) << 1;
    return temp;

}

