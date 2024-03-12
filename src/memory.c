#include <stdio.h>
#include <stdlib.h>
#include "headers/memory.h"

void init_mem(Memory* mem)
{ 
    for(uint16_t i = 0; i < 256; i++) {
        for(uint16_t j = 0; j < 256; j++) {
            mem->pages[i][j] = 0;
        }
    }

    #ifdef DEBUG
    printf("Memory initialized\n");
    #endif
}

void set_reset_vector(Memory* mem, WORD start_addr)
{
    BYTE l, h;
    h = (start_addr >> 8) & 0x00FF;
    l = start_addr & 0x00FF;

    mem->pages[255][0xFC] = l;
    mem->pages[255][0xFD] = h;

    #ifdef DEBUG
    printf("Reset vector set: Using %04x as START address\n", start_addr);
    #endif
}

void w_mem(Memory* mem, WORD addr, BYTE data)
{
    BYTE page, offset;
    page = (addr >> 8) & 0x00FF;
    offset = addr & 0x00FF;

    mem->pages[page][offset] = data;
    #ifdef DEBUG
    printf("WRITE: %02x to %04x\n", data, addr);
    #endif
}

BYTE r_mem(Memory* mem, WORD addr)
{
    BYTE page, offset;
    page = (addr >> 8) & 0x00FF;
    offset = addr & 0x00FF;

    BYTE data = mem->pages[page][offset];

    #ifdef DEBUG
    printf("READ: %02x from %04x\n", data, addr);
    #endif

    return data;
}

void log_memory(Memory* mem)
{
    for(uint16_t i = 0; i < 256; i++) {
        for(uint16_t j = 0; j < 256; j+=16) {
            printf("%02x%02x: ", i, j);
            for(uint16_t k = 0; k < 16; k++) {
                printf("%02x ", mem->pages[i][j+k]);
            }
            printf("\n");
        }
    }
}

void log_page(Memory* mem, BYTE page)
{
    for(uint16_t j = 0; j < 256; j+=16) {
        printf("%02x%02x: ", page, j);
        for(uint16_t k = 0; k < 16; k++) {
            printf("%02x ", mem->pages[page][j+k]);
        }
        printf("\n");
    }
}

void load_program(Memory* mem, const char* output)
{
    FILE* f_output = fopen(output, "r");
    uint16_t i = 0;

    if(f_output != NULL) {
        BYTE h,l;

        h = mem->pages[255][0xFD];
        l = mem->pages[255][0xFC];

        WORD start_addr = (h << 8) | l;

        #ifdef DEBUG
        printf("Program loading from: %04x\n", start_addr);
        #endif

        BYTE c = fgetc(f_output);

        while((char)c != EOF && i < 256) {
            h = (start_addr >> 8) & 0x00FF;
            l = start_addr & 0x00FF;

            mem->pages[h][l] = c;
            c = fgetc(f_output);

            start_addr++;
            i++;
        }

        #ifdef DEBUG
        printf("Program loaded\n");
        #endif

    } else {
        printf("Please specify binary files\n");
        exit(0);
    }
}
