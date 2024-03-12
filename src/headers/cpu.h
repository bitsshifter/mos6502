#pragma once
#include "types.h"
#include "memory.h"

typedef struct
{
    unsigned int c : 1; /* Carry */
    unsigned int z : 1; /* Zero */
    unsigned int i : 1; /* Interupt disable */
    unsigned int d : 1; /* Decimal mode */
    unsigned int b : 1; /* Break command */
    unsigned int v : 1; /* Overflow */
    unsigned int n : 1; /* Negative */
} STATUS;

typedef struct 
{
    WORD pc_reg;
    BYTE a_reg, x_reg, y_reg, sp_reg;
    STATUS ps_reg;
} Cpu;

void reset(Cpu* cpu, Memory* mem);
void inc_pc(Cpu* cpu);
BYTE fetch(Cpu* cpu, Memory* mem, uint8_t sync);
void log_state(Cpu* cpu);
void run(Cpu* cpu, Memory* mem);
