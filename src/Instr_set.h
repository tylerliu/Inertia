//
//  Instr_set.h
//  Inertia
//
//  Created by Tyler Liu on 2016/12/03.
//  Copyright © 2016 Tyler Liu. All rights reserved.

#ifndef Instr_set_h
#define Instr_set_h

#include <stdint.h>

//pc is RISC-V definition divided by 4

//RV32I/RV32M

//opcodes
#define OP_IMM 0b0010011//Integer Register-Immediate Instructions, type I
#define OP     0b0110011//Integer Register-Register Operations, type R
#define LUI    0b0110111//load upper immediate, type U, load imm to dest.
#define AUIPC  0b0010111//add upper immediate to pc, type U, add imm to pc, store in dest.
//MV = ADDI r1 rs 0
//NOP = ADDI x0, x0, 0
#define JAL    0b1101111//Unconditional jumps, type UJ, add immediate to pc.if dest = 0, plain jump. store pc+4 to dest after jump.
#define JALR   0b1100111//jump and link register, type I, store pc+4 to dest after jump.
#define BRANCH 0b1100011//branch statements, type SB, shift of offest.
#define LOAD   0b0000011//load from memory, type I, The effective byte = s1 + IMM.
#define STORE  0b0100011//store to memory, type S, The effective byte = s1 + IMM.
//FENCE not defined as single thread application
//SYSTEM not defined yet.
#define IO     0b0001011//custom 0, Input/Output, type I
#define FUNC   0b0101011//custom 1, function control

//func3
#define ADD  0b000 //addition
#define SLT  0b010 //signed compare
#define SLTU 0b011 //unsigned compare
#define AND  0b111 //bitwise and
#define OR   0b110 //bitwise or
#define XOR  0b100 //bitwise xor
#define SLL  0b001 //logical left shifts
#define SRL  0b101 //logical right shifts
#define SUB  0b000 //funct7 = 0b0100000, subtraction
#define SRA  0b101 //funct7 = 0b0100000, arithmetic right shifts

//branches
#define BEQ  0b000 //branch equal
#define BNE  0b001 //branch not equal
#define BLT  0b100 //branch less than
#define BLTU 0b101 //branch less than unsigned
#define BGE  0b110 //branch greater than
#define BGEU 0b111 //branch greater than unsigned

//LOAD/STORE
#define LW   0b010 //load 32 bit value from memory
#define LH   0b001 //load 16 bit value signed
#define LHU  0b101 //load 16 bit value unsigned
#define LB   0b000 //load 8 bit value signed
#define LBU  0b100 //load 8 bit value unsigned
#define SW   0b010 //store 32 bit value
#define SH   0b001 //store 16 bit value
#define SB   0b000 //store 8 bit value

//RV32M, func7 = 0b0000001
#define MUL  0b000 //return low 32 bit of product
#define MULH 0b001
#define MULHSU 0b010
#define MULHU 0b011
#define DIV  0b100
#define DIVU 0b101
#define REM 0b110
#define REMU 0b111



//RV32F/RV32D

//opcodes
#define LOAD_FP   0b0000111//load from memory, type I, The effective byte = s1 + IMM. floating point
#define STORE_FP  0b0100111//store to memory, type S, The effective byte = s1 + IMM. floating point
#define OP_FP     0b1010011//floating point Operations, type R4
#define FMADD     0b1000011//rs1 * rs2 + rs3, type R4
#define FMSUB     0b1000111//rs1 * rs2 - rs3, type R4
#define FNMADD    0b1001111//-(rs1 * rs2 + rs3), type R4
#define FNMSUB    0b1001011//-(rs1 * rs2 - rs3), type R4

//width, store in func3
#define FLT 0b010 //width of floating point
#define DLE 0b011 //width of double
//#define QFL 0b111 //width of long double

//fmt
#define FMT_S 0b00 //width of floating point
#define FMT_D 0b01 //width of double precision floating point
#define FMT_Q 0b11 //width of quad precision floating point

//OP_FP, FMAX/FMIN not supported, 64 bit int not supported, code in rs3
//rounding mode not supported, using nearest
//all treated as double in operation
#define FADD 0b00000  //floating point addiction
#define FSUB 0b00001  //floating point subtraction
#define FMUL 0b00010  //floating point multiplication
#define FDIV 0b00011  //floating point division
#define FSQRT 0b01011 //floating point equare root
#define FCVT_fmt_int 0b11010 //int32_t to floating point
#define FCVT_int_fmt 0b11000 //floating point to int32_t
//rs2 = 00001 if W as unsigned,
#define FCMP      0b10100 //floating point comparing.

//FCMP func3
#define F_EQ 0b010 //floating point equal
#define F_LT 0b001 //floating point less than
#define F_LE 0b000 //floating point less than or equal

//FSGNJ, FMV not defined
//FCLASS not defined

//IO
//see decode function

//FUNC
//call

//call: need to be follow by JAL/JALR to move to function
//call with reg
//return
//exit()
//realloc(), after dynamic alloc done


//enumerators

//Structures
typedef struct{
    unsigned int opcode:7;
    unsigned int rd:5;
    unsigned int funct3:3;
    unsigned int rs1:5;
    unsigned int rs2:5;
    unsigned int funct7:7;
}Instr_format_R;

typedef struct{
    unsigned int opcode:7;
    unsigned int rd:5;
    unsigned int funct3:3;
    unsigned int rs1:5;
    unsigned int rs2:5;
    unsigned int funct2:2;
    unsigned int rs3:5;
}Instr_format_R4;

typedef struct{
    unsigned int opcode:7;
    unsigned int rd:5;
    unsigned int funct3:3;
    unsigned int rs1:5;
    unsigned int imm0_11:12;
}Instr_format_I;

typedef struct{
    unsigned int opcode:7;
    unsigned int imm0_4:5;
    unsigned int funct3:3;
    unsigned int rs1:5;
    unsigned int rs2:5;
    unsigned int imm5_11:7;
}Instr_format_S;

typedef struct{
    unsigned int opcode:7;
    unsigned int imm11:1;
    unsigned int imm1_4:4;
    unsigned int funct3:3;
    unsigned int rs1:5;
    unsigned int rs2:5;
    unsigned int imm5_10:6;
    unsigned int imm12:1;
}Instr_format_SB;

typedef struct{
    unsigned int opcode:7;
    unsigned int rd:5;
    unsigned int imm12_31:20;
}Instr_format_U;

typedef struct{
    unsigned int opcode:7;
    unsigned int rd:5;
    unsigned int imm12_19:8;
    unsigned int imm11:1;
    unsigned int imm1_10:10;
    unsigned int imm20:1;
}Instr_format_UJ;

//functions
int32_t get_imm_I(Instr_format_I *);
int32_t get_imm_S(Instr_format_S *);
int32_t get_imm_SB(Instr_format_SB *);
int32_t get_imm_U(Instr_format_U *);
int32_t get_imm_UJ(Instr_format_UJ *);

#endif /* Instr_set.h */