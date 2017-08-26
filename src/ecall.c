//
// Created by Tyler on 2017/08/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ecall.h"
#include "RegMem.h"

#define num_set 2
#define num_func 20

void (*ecall_func[num_set][num_func])() = {
        {Exit},
        {print_char, print_int, print_double, print_string, read_char, read_int, read_double, read_string,
                file_open, file_close, file_flush, file_rewind, file_tell, file_seek, file_eof, file_error, file_write, file_read},
        {mem_alloc, mem_free, mem_realloc, mem_print_stat}
};

void ecall_funct(uint8_t set, uint32_t func){
    (ecall_func[set][func])();
}



void Exit(){
    running = 0;
}

uint32_t len_files = 8;
uint32_t used_files;
FILE **files;
void io_init(){
    files = malloc(len_files * sizeof(FILE *));
    files[1] = stdin;
    files[2] = stdout;
    files[3] = stderr;
    used_files = 4;
}

void io_free(){
    free(files);
}

//IO handling
void print_char(){
    putchar(int_regs[6]);
}

void print_int(){
    printf("%d", int_regs[6]);
}

void print_double(){
    printf("%lf", fpt_regs[1]);
}

void print_string(){
    printf("%s", (char *)(memory + int_regs[6]));
}

void read_char(){
    int_regs[6] = getchar();
}

void read_int(){
    scanf("%d", &int_regs[6]);
}

void read_double(){
    scanf("%lf", &fpt_regs[1]);
}

void read_string(){
    scanf("%s", (char *)(memory + int_regs[6]));
}

void file_open(){
    if (len_files == used_files) {
        len_files <<= 1;
        files = realloc(files, len_files * sizeof(FILE *));
    }
    files[used_files] = fopen((char *)(memory + int_regs[6]), (char *)(memory + int_regs[7]));
    int_regs[6] = used_files;
    used_files ++;
}

void file_close(){
    fclose(files[int_regs[6]]);
    if (int_regs[6] >= 3 && int_regs[6] == used_files - 1) used_files --;
}
 
void file_flush(){
    int_regs[6] = fflush(files[int_regs[6]]);
}

void file_rewind(){
    rewind(files[int_regs[6]]);
}

void file_tell(){
    int_regs[6] = (uint32_t)ftell(files[int_regs[6]]);
}

void file_seek(){
    int_regs[6] = fseek(files[int_regs[6]], int_regs[7], int_regs[8]);
}

void file_eof(){
    feof(files[int_regs[6]]);
}

void file_error(){
    ferror(files[int_regs[6]]);
}

void file_write(){
    int_regs[6] = (uint32_t)fwrite(memory + int_regs[6], 1, int_regs[7], files[int_regs[8]]);
}

void file_read(){
    int_regs[6] = (uint32_t)fread(memory + int_regs[6], 1, int_regs[7], files[int_regs[8]]);
}


void mem_alloc(){
    int_regs[6] = alloc_block((uint32_t)int_regs[6]);
}
void mem_free(){
    free_block((uint32_t)int_regs[6]);
}
void mem_realloc(){
    int_regs[6] = realloc_block((uint32_t)int_regs[6], (uint32_t)int_regs[7]);
}
void mem_print_stat(){
    print_heap_stat();
}