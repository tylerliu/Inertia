//
//  Instr_set.h
//  Inertia
//
//  Created by Tyler Liu on 2016/12/03.
//  Copyright © 2016 Tyler Liu. All rights reserved.

#ifndef Instr_set_h
#define Instr_set_h

#include <stdint.h>

//opcodes

//imm ops
#define ADDI    0X00
#define SLTI    0X01
#define SLTUI   0X02
#define ANDI    0X03
#define ORI     0X04
#define XORI    0X05
#define SLLI    0X06
#define SRLI    0X07
#define SRAI    0X08
#define MULI    0X09
#define DIVI    0X0A
#define DIVUI   0X0B
#define REMI    0X0C
#define REMUI   0X0D
#define ADD     0X0E
#define SUB     0X0F
#define SLT     0X10
#define SLTU    0X11
#define AND     0X12
#define OR      0X13
#define XOR     0X14
#define SLL     0X15
#define SRL     0X16
#define SRA     0X17
#define MUL     0X18
#define DIV     0X19
#define DIVU    0X1A
#define REM     0X1B
#define REMU    0X1C
#define LUI     0X1D
#define AUIPC   0X1E
#define JAL     0X1F
#define JALR    0X20
#define BEQ     0X21
#define BNE     0X22
#define BLT     0X23
#define BLTU    0X24
#define BGE     0X25
#define BGEU    0X26
#define LW      0X27
#define LH      0X28
#define LHU     0X29
#define LB      0X2A
#define LBU     0X2B
#define SW      0X2C
#define SH      0X2D
#define SB      0X2E
#define FLW     0X2F
#define FLD     0X30
#define FSW     0X31
#define FSD     0X32
#define FADD    0X33
#define FSUB    0X34
#define FMUL    0X35
#define FDIV    0X36
#define FSQRT   0X37
#define FCVT_D_W 0X38
#define FCVT_D_WU 0X39
#define FCVT_W_D 0X3A
#define FCVT_WU_D 0X3B
#define F_EQ    0X3C
#define F_LT    0X3D
#define F_LE    0X3E
#define FMV     0X3F
#define FNEG    0X40
#define FABS    0X41
#define ECALL   0X42



//func3
// ADD   //addition
// SLT   //signed compare
// SLTU  //unsigned compare
// AND   //bitwise and
// OR    //bitwise or
// XOR   //bitwise xor
// SLL   //logical left shifts
// SRL   //logical right shifts
// SUB   //subtraction
// SRA   //arithmetic right shifts

//LUI load upper immediate, type U, load imm to dest.
//AUIPC add upper immediate to pc, type U, load imm + pc to dest.
//JAL Unconditional jumps, type UJ, add immediate to pc.if dest = 0, plain jump. store pc+1 to dest after jump.(next instr)
//JALR jump and link register, type I, store pc+4 to dest after jump.(next instr)

//branches
// BEQ   //branch equal
// BNE   //branch not equal
// BLT   //branch less than
// BLTU  //branch less than unsigned
// BGE   //branch greater than
// BGEU  //branch greater than unsigned

//LOAD/STORE
// LW    //load 32 bit value from memory
// LH    //load 16 bit value signed
// LHU   //load 16 bit value unsigned
// LB    //load 8 bit value signed
// LBU   //load 8 bit value unsigned
// SW    //store 32 bit value
// SH    //store 16 bit value
// SB    //store 8 bit value

// LOAD_FP   //load from memory, type I, The effective byte = s1 + IMM. floating point
// STORE_FP  //store to memory, type S, The effective byte = s1 + IMM. floating point
// OP_FP     //floating point Operations, type R4

//OP_FP, FMAX/FMIN not supported, 64 bit int not supported, code in rs3
//rounding mode not supported, using nearest
//all treated as double in operation
// FADD   //floating point addiction
// FSUB   //floating point subtraction
// FMUL   //floating point multiplication
// FDIV   //floating point division
// FSQRT  //floating point equare root
// FCVT_fmt_int  //int32_t to floating point
// FCVT_int_fmt  //floating point to int32_t

// F_EQ  //floating point equal
// F_LT  //floating point less than
// F_LE  //floating point less than or equal

//FMV    //floating point move
//FNEG   //floating point negation
//FABS   //floating point absolute value

//IO
//see decode function

//FUNC
//call

//call with reg
//return
//exit()
//realloc(), after dynamic alloc done


//enumerators

//Structures
typedef struct{
    unsigned int opcode:8;
    unsigned int rd:5;
    unsigned int rs1:5;
    unsigned int rs2:5;
    unsigned int funct:9;
}Instr_format_R;

typedef struct{
    unsigned int opcode:8;
    unsigned int rd:5;
    unsigned int rs1:5;
    unsigned int imm:14;
}Instr_format_I;

typedef struct{
    unsigned int opcode:8;
    unsigned int rs1:5;
    unsigned int rs2:5;
    unsigned int imm:14;
}Instr_format_S;

typedef struct{
    unsigned int opcode:8;
    unsigned int rd:5;
    unsigned int imm:19;
}Instr_format_U;

//functions
int32_t get_imm_I(Instr_format_I *);
int32_t get_imm_S(Instr_format_S *);
int32_t get_imm_U(Instr_format_U *);
int32_t get_imm_UJ(Instr_format_U *);

#endif /* Instr_set.h */