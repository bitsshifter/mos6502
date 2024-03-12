#pragma once
#include "types.h"

typedef struct
{
  BYTE pages[256][256];
} Memory;

void init_mem(Memory* mem);
void set_reset_vector(Memory* mem, WORD start_addr);
void w_mem(Memory* mem, WORD addr, BYTE data);
BYTE r_mem(Memory* mem, WORD addr);
void log_memory(Memory* mem);
void log_page(Memory* mem, BYTE page);
void load_program(Memory* mem, const char* output);
