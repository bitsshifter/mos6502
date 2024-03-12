#include <stdio.h>
#include "headers/types.h"
#include "headers/cpu.h"
#include "headers/memory.h"
#include "headers/ops.h"

void reset(Cpu* cpu, Memory* mem)
{
    BYTE h, l;
    h = r_mem(mem, 0xFFFD);
    l = r_mem(mem, 0xFFFC);
    cpu->pc_reg = (h << 8) | l;
    cpu->sp_reg = 0x00;

    #ifdef DEBUG
    printf("PC set (HEX): %04x\nSP set (HEX): %04x\n", cpu->pc_reg, cpu->sp_reg);
    #endif 
}

void inc_pc(Cpu* cpu)
{
    ++(cpu->pc_reg);
    #ifdef DEBUG
    printf("PC incremented to (HEX): %04x\n", cpu->pc_reg);
    #endif
}

BYTE fetch(Cpu* cpu, Memory* mem, uint8_t sync)
{
    BYTE data = r_mem(mem, cpu->pc_reg);

    #ifdef DEBUG
    if(sync) {
        printf("Instruction fetch\n");
    }
    printf("Fetched: %02x from address: %04x\n", data, cpu->pc_reg);
    #endif

    inc_pc(cpu);
    return data;
}

void log_state(Cpu* cpu)
{
  printf("PC: %04x\nA: %02x\nX: %02x\nY: %02x\nSP: %02x\n", cpu->pc_reg, cpu->a_reg, cpu->x_reg, cpu->y_reg, cpu->sp_reg);
}

void run(Cpu* cpu, Memory* mem)
{
    uint8_t running = 1;
    while(running)
    {
        BYTE opcode = fetch(cpu, mem, 1);

        switch (opcode)
        {
            case 0xEA:
                nop(cpu);
                break;
            case 0xA4:
                ldy_zp(cpu, mem);
                break;
            case 0xA5:
                lda_zp(cpu, mem);
                break;
            case 0xA6:
                ldx_zp(cpu, mem);
                break;
            default:
                printf("Illegal opcode...CRASH\n");
                log_state(cpu);
                running = 0;
            break;
        }
    }
}
