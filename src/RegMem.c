//
//  RegMem.c
//  Inertia
//
//  Created by Tyler Liu on 2016/12/03.
//  Copyright © 2016 Tyler Liu. All rights reserved.
//
//  Register and Memory model

#include <stdlib.h>
#include <printf.h>
#include <memory.h>
#include <errno.h>
#include "RegMem.h"
#include "Execution.h"

//heap block prefix structure
/*
 * uint32_t prev;
 * uint32_t next;
 * uint32_t is_used;
 * char ptr[0];
 */
 
#define BLOCK_PREV_OF(ptr) (*(uint32_t *)(memory + (ptr)))
#define BLOCK_NEXT_OF(ptr) (*(uint32_t *)(memory + (ptr) + 4))
#define BLOCK_IS_USED(ptr) (*(uint32_t *)(memory + (ptr) + 8))
#define BLOCK_SIZE(ptr) (BLOCK_NEXT_OF(ptr) == 0 ? heap_brk - (ptr) - 12 : BLOCK_NEXT_OF(ptr) - (ptr) - 12)

void init_heap(){
    heap_brk = heap_start + 12;
    memset(memory + heap_start, 0, 12);
}

uint32_t heap_sbrk(uint32_t size){
    if (heap_brk > int_regs[3]) {
        running = 0;
        fprintf(stderr, "ERROR: STACK OVERFLOW");
    }
    if (heap_brk + size > int_regs[3]) {
        return 0;
    }
    heap_brk += size;
    return heap_brk;
}

uint32_t alloc_block(uint32_t size){
    size = ((size - 1) >> 2 << 2) + 4;

    uint32_t loc = heap_start;
    while (BLOCK_NEXT_OF(loc) != 0 && (BLOCK_IS_USED(loc) == 1 || (BLOCK_SIZE(loc)) < size))
        loc = BLOCK_NEXT_OF(loc);

    // if it is the last one
    if (BLOCK_NEXT_OF(loc) == 0) {
        if (BLOCK_IS_USED(loc) == 1) {
            //used
            BLOCK_NEXT_OF(loc) = heap_brk;
            if (heap_sbrk(size + 12) == 0) {
                BLOCK_NEXT_OF(loc) = 0;
                return 0;
            }
            BLOCK_PREV_OF(BLOCK_NEXT_OF(loc)) = loc;
            loc = BLOCK_NEXT_OF(loc);
            BLOCK_NEXT_OF(loc) = 0;
            BLOCK_IS_USED(loc) = 1;
            return loc + 12;
        }
        //this block is free
        if (heap_brk - loc < size + 24 && heap_sbrk(size + 24 - (heap_brk - loc)) == 0){
            return 0;
        }
        //split block
        BLOCK_NEXT_OF(loc) = loc + size + 12;
        *(uint32_t *)(memory + loc + size + 12) = loc;
        *(uint32_t *)(memory + loc + size + 16) = 0;
        *(uint32_t *)(memory + loc + size + 20) = 0;
        BLOCK_IS_USED(loc) = 1;
        return loc + 12;
    }

    if (BLOCK_SIZE(loc) >= size && BLOCK_IS_USED(loc) == 0) {
        //usable block
        BLOCK_IS_USED(loc) = 1;
        if (BLOCK_SIZE(loc) >= size + 16){
            //split block
            uint32_t new = loc + 12 + size;
            BLOCK_PREV_OF(new) = loc; // prev
            BLOCK_NEXT_OF(new) = BLOCK_NEXT_OF(loc); // next
            BLOCK_IS_USED(new) = 0;
            BLOCK_NEXT_OF(loc) = new;
            BLOCK_PREV_OF(BLOCK_NEXT_OF(new)) = new;
        }
        return loc + 12;
    }

    return 0;
}

void free_block(uint32_t ptr){
    ptr -= 12;
    if (ptr < heap_start || ptr + 12 >= heap_brk
            || (BLOCK_PREV_OF(ptr) != 0 && BLOCK_NEXT_OF(BLOCK_PREV_OF(ptr)) != ptr) || (BLOCK_NEXT_OF(ptr) != 0 && BLOCK_PREV_OF(BLOCK_NEXT_OF(ptr)) != ptr)){
        fprintf(stderr, "Error on freeing heap block");
        return;
    }

    BLOCK_IS_USED(ptr) = 0;
    if (BLOCK_PREV_OF(ptr) != 0 && BLOCK_IS_USED(BLOCK_PREV_OF(ptr)) == 0){
        //combine previous
        BLOCK_NEXT_OF(BLOCK_PREV_OF(ptr)) = BLOCK_NEXT_OF(ptr);
        BLOCK_PREV_OF(BLOCK_NEXT_OF(ptr)) = BLOCK_PREV_OF(ptr);
        ptr = BLOCK_PREV_OF(ptr);
    }

    if (BLOCK_NEXT_OF(ptr) != 0 && BLOCK_IS_USED(BLOCK_NEXT_OF(ptr)) == 0){
        //combine next
        BLOCK_NEXT_OF(ptr) = BLOCK_NEXT_OF(BLOCK_NEXT_OF(ptr));
        BLOCK_PREV_OF(BLOCK_NEXT_OF(ptr)) = ptr;
    }
}

uint32_t realloc_block(uint32_t ptr, uint32_t size){
    size = ((size - 1) >> 2 << 2) + 4;
    ptr -= 12;
    if (ptr < heap_start || ptr + 12 >= heap_brk
        || (BLOCK_PREV_OF(ptr) != 0 && BLOCK_NEXT_OF(BLOCK_PREV_OF(ptr)) != ptr) || (BLOCK_NEXT_OF(ptr) != 0 && BLOCK_PREV_OF(BLOCK_NEXT_OF(ptr)) != ptr)){
        fprintf(stderr, "Error on reallocating heap block");
        return 0;
    }

    //combine previous
    if (BLOCK_PREV_OF(ptr) != 0 && !BLOCK_IS_USED(BLOCK_PREV_OF(ptr)) && (BLOCK_SIZE(BLOCK_PREV_OF(ptr)) + BLOCK_SIZE(ptr) + 12 >= size || //combine prev block needed only
            (BLOCK_NEXT_OF(ptr) != 0 && !BLOCK_IS_USED(BLOCK_NEXT_OF(ptr)) && BLOCK_SIZE(BLOCK_PREV_OF(ptr)) + BLOCK_SIZE(ptr) + BLOCK_NEXT_OF(ptr) + 24 >= size) //combine next block too
            || (BLOCK_NEXT_OF(ptr) == 0 && heap_sbrk(size - (BLOCK_SIZE(BLOCK_PREV_OF(ptr)) + BLOCK_SIZE(ptr) + 12)) != 0) //combine prev && map more
            || (BLOCK_NEXT_OF(ptr) != 0 && BLOCK_NEXT_OF(BLOCK_NEXT_OF(ptr)) == 0 && BLOCK_IS_USED(BLOCK_NEXT_OF(ptr)) == 0 && heap_sbrk(size - (BLOCK_SIZE(BLOCK_PREV_OF(ptr)) + BLOCK_SIZE(ptr) + BLOCK_SIZE(BLOCK_NEXT_OF(ptr)) + 24)) != 0)
            )) {
        //combine previous
        BLOCK_NEXT_OF(BLOCK_PREV_OF(ptr)) = BLOCK_NEXT_OF(ptr);
        BLOCK_PREV_OF(BLOCK_NEXT_OF(ptr)) = BLOCK_PREV_OF(ptr);
        BLOCK_IS_USED(BLOCK_PREV_OF(ptr)) = 1;
        int original = ptr;
        ptr = BLOCK_PREV_OF(ptr);
        memmove(memory + ptr + 12, memory + original + 12, BLOCK_SIZE(ptr));

    }

    if (BLOCK_NEXT_OF(ptr) == 0 && BLOCK_SIZE(ptr + 12) < size){
        heap_sbrk(size - BLOCK_SIZE(ptr));
    }

    if (BLOCK_NEXT_OF(ptr) != 0 && BLOCK_NEXT_OF(BLOCK_NEXT_OF(ptr)) == 0 && BLOCK_SIZE(ptr) + BLOCK_SIZE(BLOCK_NEXT_OF(ptr)) + 12 < size)
        heap_sbrk(size - BLOCK_SIZE(ptr) - BLOCK_SIZE(BLOCK_NEXT_OF(ptr)));

    if (BLOCK_NEXT_OF(ptr) != 0 && !BLOCK_IS_USED(BLOCK_NEXT_OF(ptr)) && BLOCK_SIZE(BLOCK_NEXT_OF(ptr)) + BLOCK_SIZE(ptr) + 12 >= size) {
        //combine next
        BLOCK_NEXT_OF(ptr) = BLOCK_NEXT_OF(BLOCK_NEXT_OF(ptr));
        BLOCK_PREV_OF(BLOCK_NEXT_OF(ptr)) = ptr;
    }

    //spilt left
    if (BLOCK_SIZE(ptr) >= size + 16 || (BLOCK_NEXT_OF(ptr) == 0 && BLOCK_SIZE(ptr) >= size + 12)) {
        //split block
        uint32_t new = ptr + 12 + size;
        BLOCK_PREV_OF(new) = ptr; // prev
        BLOCK_NEXT_OF(new) = BLOCK_NEXT_OF(ptr); // next
        BLOCK_IS_USED(new) = 0;
        BLOCK_NEXT_OF(ptr) = new;
        BLOCK_PREV_OF(BLOCK_NEXT_OF(new)) = new;
        return ptr + 12;
    }

    if (BLOCK_SIZE(ptr) >= size) return ptr + 12;

    //last
    uint32_t new = alloc_block(size);
    if (new == 0) return 0;
    memcpy(memory + ptr + 12, memory + new, BLOCK_SIZE(ptr));
    //free
    free_block(ptr + 12);
    return new;
}

void print_heap_stat(){
    uint32_t ptr = heap_start;
    printf("----------------------- BLOCK STAT --------------------------\n");
    printf("heap start: %d, heap break: %d\n", heap_start, heap_brk);
    while (ptr){
        printf("block: prev: %u,\tcurr: %u,\tnext: %u,\tsize: %u,\tis %s\n", BLOCK_PREV_OF(ptr), ptr, BLOCK_NEXT_OF(ptr), BLOCK_SIZE(ptr), BLOCK_IS_USED(ptr) ? "RESERVED" : "FREE" );
        ptr = BLOCK_NEXT_OF(ptr);
    }
    printf("--------------------- BLOCK STAT END ------------------------\n");
}