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
    if ((*(int32_t *)instr) >> 31) temp = ~0x3FFF;
    return temp + instr->imm;
}

int32_t get_imm_S(Instr_format_S *instr){
    int32_t temp = 0;
    if ((*(int32_t *)instr) >> 31) temp = ~0x3FFF;
    return temp + instr->imm;
}

int32_t get_imm_U(Instr_format_U *instr){
    int32_t temp = instr->imm << 13;//12-31
    return temp;
}

int32_t get_imm_UJ(Instr_format_U *instr){
    int32_t temp = 0;
    if ((*(int32_t *)instr) >> 31) temp = ~0x7FFFF;
    return temp + instr->imm;

}

