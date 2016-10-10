//
//  main.c
//  Inertia
//
//  Created by Tyler Liu on 2016/10/09.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//

#include <stdio.h>

#define NUM_REGS 4

#define NUM_MEMS 256

#define INERTIA_ADD 0x0 // Integer Addition
#define INERTIA_DIV 0x1 // Integer Division
#define INERTIA_MUL 0x2 // Integer Multiplication

#define INERTIA_ILT 0x3 // Integer Less Than
#define INERTIA_IEQ 0x4 // Integer Equal To
#define INERTIA_AND 0x5 // Bitwise AND
#define INERTIA_NOT 0x6 // Bitwise NOT
#define INERTIA_OR 0x7 //  Bitwise OR
#define INERTIA_SHIFTL 0x8 //Bitwise SHIFTL
#define INERTIA_SHIFTR 0x9 //Bitwise SHIFTR

#define INERTIA_PROCEDURE 0xA // Initialize Concept Procedure OUTPUT
#define INERTIA_PRINT 0xB // Print to stdout
#define INERTIA_LOAD 0xC // Load value
#define INERTIA_BRANCH 0xD //branch / goto
#define INERTIA_IF 0xE //branch / if
#define INERTIA_RETURN 0xF //return


unsigned regs[ NUM_REGS ];
unsigned memory [ NUM_MEMS ];
unsigned program[] = { 0x1064, 0x11C8, 0x2201, 0x0000 };
int cons[3];

/* program counter */
int pc = 0;

/* fetch the next word from the program */
int fetch() {
    return program[pc++];
}

/* instruction fields */
int instrNum = 0;
int reg1     = 0;//-1 as const, 0-3 as register, >=4 as memory
int reg2     = 0;
int reg3     = 0;
int imm      = 0;

/* decode a word */
void decode( int instr )  {
    int dcut = 0;
    
    instrNum = instr >> 28;
    instr = instr << 4;
    if (((instr >>  31) & 1 )== 0) {
        reg1 = 4;
        instr = instr << 1;
        dcut ++;
    }//memory
    else if (((instr >> 30) & 3) == 2) {
        reg1 = 1;//register
        instr = instr << 2;
        dcut += 2;
    }
    else {
        reg1 = -1;
        instr = instr << 2;
        dcut += 2;
    }
    
    if (((instr >>  31) & 1 )== 0) {
        reg2 = 4;
        instr = instr << 1;
        dcut ++;
    }//memory
    else if (((instr >> 30) & 3) == 2) {
        reg2 = 1;//register
        instr = instr << 2;
        dcut += 2;
    }
    else {
        reg2 = -1;
        instr = instr << 2;
        dcut += 2;
    }
    
    if (((instr >>  31) & 1 )== 0) {
        reg3 = 4;
        instr = instr << 1;
        dcut ++;
    }//memory
    else if (((instr >> 30) & 3) == 2) {
        reg3 = 1;//register
        instr = instr << 2;
        dcut += 2;
    }
    else {
        reg3 = -1;
        instr = instr << 2;
        dcut += 2;
    }
    
    if (reg1 == 1) {
        reg1 = (instr >> 30);
        instr = instr << 2;
        dcut += 2;
    }
    
    if (reg2 == 1) {
        reg2 = (instr >> 30);
        instr = instr << 2;
        dcut += 2;
    }
    
    if (reg3 == 1) {
        reg3 = (instr >> 30);
        instr = instr << 2;
        dcut += 2;
    }
    
    if (dcut == 3){
        instr = instr << 1;
    }
    if (dcut > 4 && dcut < 12){
        instr = instr << (12 - dcut);
    }
    
    if (reg1 == 4){
        reg1 = (instr >> 24) + 4;
        instr = instr << 8;
    }
    
    if (reg2 == 4){
        reg2 = (instr >> 24) + 4;
        instr = instr << 8;
    }
    
    if (reg3 == 4){
        reg3 = (instr >> 24) + 4;
        instr = instr << 8;
    }
    
    if (reg1 == -1){
        cons[0] = fetch();
    }
    
    if (reg2 == -1){
        cons[1] = fetch();
    }
    
    if (reg3 == -1){
        cons[2] = fetch();
    }
}

/* the VM runs until this flag becomes 0 */
int running = 1;

/* evaluate the last decoded instruction */
void eval()
{
    switch( instrNum )
    {
        case 0:
            /* halt */
            printf( "halt\n" );
            running = 0;
            break;
        case 1:
            /* loadi */
            printf( "loadi r%d #%d\n", reg1, imm );
            regs[ reg1 ] = imm;
            break;
        case 2:
            /* add */
            printf( "add r%d r%d r%d\n", reg1, reg2, reg3 );
            regs[ reg1 ] = regs[ reg2 ] + regs[ reg3 ];
            break;
    }
}

/* display all registers as 8-digit hexadecimal words */
void showRegs()
{
    int i;
    printf( "regs = " );
    for( i=0; i<NUM_REGS; i++ )
        printf( "%04X ", regs[ i ] );
    printf( "\n" );
}

void run()
{
    while( running )
    {
        showRegs();
        int instr = fetch();
        decode( instr );
        eval();
    }
    showRegs();
}

int main( int argc, const char * argv[] )
{
    run();
    return 0;
}