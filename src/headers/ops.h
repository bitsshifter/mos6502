#pragma once
#include "types.h"
#include "memory.h"
#include "cpu.h"

void nop(Cpu* cpu);                   /* OPCODE: 0xEA */
void ldy_zp(Cpu* cpu, Memory* mem);   /* OPCODE: 0xA4 */
void lda_zp(Cpu* cpu, Memory* mem);   /* OPCODE: 0xA5 */
void ldx_zp(Cpu* cpu, Memory* mem);   /* OPCODE: 0xA6 */
void ldy_a(Cpu* cpu, Memory* mem);    /* OPCODE: 0xAC */
void lda_a(Cpu* cpu, Memory* mem);    /* OPCODE: 0xAD */
void ldx_y(Cpu* cpu, Memory* mem);    /* OPCODE: 0xAE */
void sty_zp(Cpu* cpu, Memory* mem);   /* OPCODE: 0x84 */
void sta_zp(Cpu* cpu, Memory* mem);   /* OPCODE: 0x85 */
void stx_zp(Cpu* cpu, Memory* mem);   /* OPCODE: 0x86 */
void sty_a(Cpu* cpu, Memory* mem);    /* OPCODE: 0x8C */
void sta_a(Cpu* cpu, Memory* mem);    /* OPCODE: 0x8D */
void stx_a(Cpu* cpu, Memory* mem);    /* OPCODE: 0x8E */
void ldy_zp_x(Cpu* cpu, Memory* mem); /* OPCODE: 0xB4 */
void lda_zp_x(Cpu* cpu, Memory* mem); /* OPCODE: 0x */
void ldx_zp_y(Cpu* cpu, Memory* mem);
void ldy_a_x(Cpu* cpu, Memory* mem);
void lda_a_x(Cpu* cpu, Memory* mem);
void ldx_a_y(Cpu* cpu, Memory* mem);
void sty_zp_x(Cpu* cpu, Memory* mem);
void sta_zp_x(Cpu* cpu, Memory* mem);
void stx_zp_y(Cpu* cpu, Memory* mem);
void sta_a_y(Cpu* cpu, Memory* mem);
void sta_a_x(Cpu* cpu, Memory* mem);
void ldy_im(Cpu* cpu, Memory* mem);
void ldx_im(Cpu* cpu, Memory* mem);
void lda_im(Cpu* cpu, Memory* mem);

// Add more later
