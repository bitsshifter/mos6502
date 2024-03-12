#include "headers/types.h"
#include "headers/memory.h"
#include "headers/cpu.h"

static WORD assemble_pc(BYTE l, BYTE h)
{
    return (h << 8) | l;
}


// NOP
void nop() { ;; }

/*
    ABSOLUTE ADDRESSING MODE 
    ------------------------
*/


/* LDY zp: 0xA4 */
void ldy_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    BYTE data = r_mem(mem, zp_addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->y_reg = data;
}

/* LDA zp: 0xA5 */
void lda_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    BYTE data = r_mem(mem, zp_addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->a_reg = data;
}

/* LDX zp: 0xA6 */
void ldx_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    BYTE data = r_mem(mem, zp_addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;
    cpu->x_reg = data;
}

/* LDY a: 0xAC */
void ldy_a(Cpu* cpu, Memory* mem) // OVO PROVJERI OBAVEZNO!!!
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);

    BYTE data = r_mem(mem, addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->y_reg = data;
}

/* LDA a: 0xAD */
void lda_a(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);

    cpu->a_reg = r_mem(mem, addr);
}

/* LDX a: 0xAE */
void ldx_a(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);
    BYTE data = r_mem(mem, addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->x_reg = data;
}

/* LDA a,y: 0xB9 */
void lda_a_y(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr) + cpu->y_reg;

    BYTE data = r_mem(mem, addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0xF0) >> 8;

    cpu->a_reg = data;
}

/* STY zp: 84 */
void sty_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);

    w_mem(mem, zp_addr, cpu->y_reg);
}

/* STA zp: 85 */
void sta_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);

    w_mem(mem, zp_addr, cpu->a_reg);
}

/* STA zp: 86 */
void stx_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);

    w_mem(mem, zp_addr, cpu->x_reg);
}

/* STY a: 8C */
void sty_a(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);

    w_mem(mem, addr, cpu->y_reg);
}


/* STY a: 8D */
void sta_a(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);

    w_mem(mem, addr, cpu->a_reg);
}

/* STY a: 8E */
void stx_a(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);

    w_mem(mem, addr, cpu->x_reg);
}


/*
    ABSOLUTE ADDRESSING MODE WITH X and Y
    ------------------------
*/

/* LDY zp, x: B4 */
void ldy_zp_x(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    zp_addr += cpu->x_reg;

    BYTE data = r_mem(mem, zp_addr);
    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->y_reg = data; 
}

/* LDA zp, x: B5 */
void lda_zp_x(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    zp_addr += cpu->x_reg;

    BYTE data = r_mem(mem, zp_addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->a_reg = data;
}

/* LDX zp, y: B6 */
void ldx_zp_y(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    zp_addr += cpu->y_reg;
    
    BYTE data = r_mem(mem, zp_addr);
    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->x_reg = data;
}

/* LDY a, x: BC */
void ldy_a_x(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr) + cpu->x_reg;

    BYTE data = r_mem(mem, addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->y_reg = data;
}

/* LDA a, x: BD */
void lda_a_x(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr) + cpu->x_reg;

    BYTE data = r_mem(mem, addr);
    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->a_reg = data;
}

/* LDX a, y: BE */
void ldx_a_y(Cpu* cpu, Memory* mem)
{

    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr) + cpu->y_reg;

    BYTE data = r_mem(mem, addr);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;

    cpu->x_reg = addr;
}

/* STY zp, x: 94 */
void sty_zp_x(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    zp_addr += cpu->x_reg;

    w_mem(mem, zp_addr, cpu->y_reg);
}

/* STA zp, x: 0x95 */
void sta_zp_x(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    zp_addr += cpu->x_reg;

    w_mem(mem, zp_addr, cpu->a_reg);
}

/* STX zp, y: 0x96 */
void stx_zp_y(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    zp_addr += cpu->y_reg;

    w_mem(mem, zp_addr, cpu->x_reg);
}

/* STA a, y: 0x99 */
void sta_a_y(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr) + cpu->y_reg;

    w_mem(mem, addr, cpu->a_reg);
}

/* STA a, y: 0x99 */
void sta_a_x(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr) + cpu->x_reg;

    w_mem(mem, addr, cpu->a_reg);
}

/* CPY zp: 0xC4 */
void cpy_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    BYTE data = r_mem(mem, zp_addr);

    if(cpu->y_reg >= data) {
        cpu->ps_reg.c = 1;
    }
    if(cpu->y_reg == data) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = ((cpu->y_reg + data) & 0xF0) >> 8;
}

/* CMP zp: 0xC5 */
void cmp_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    BYTE data = r_mem(mem, zp_addr);

    if(cpu->a_reg >= data) {
        cpu->ps_reg.c = 1;
    }
    if(cpu->a_reg == data) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = ((cpu->a_reg + data) & 0xF0) >> 8;
}

/* DEC zp: 0xC6 */
void dec_zp(Cpu* cpu, Memory* mem)
{
    BYTE zp_addr = fetch(cpu, mem, 1);
    BYTE data = r_mem(mem, zp_addr);

    if(--data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0xF0) >> 8;
    w_mem(mem, zp_addr, data);
}

/* CPY a: 0xCC */
void cpy_a(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);
    BYTE data = r_mem(mem, addr);

    if(cpu->y_reg >= data) {
        cpu->ps_reg.c = 1;
    }
    if(cpu->y_reg == data) {
        cpu->ps_reg.z = 1;
    }
}

/* CMP a: 0xCD */
void cmp_a(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);
    BYTE data = r_mem(mem, addr);

    if(cpu->a_reg >= data) {
        cpu->ps_reg.c = 1;
    }
    if(cpu->a_reg == data) {
        cpu->ps_reg.z = 1;
    }
}

/* DEC a: 0xCE */
void dec_a(Cpu* cpu, Memory* mem)
{
    BYTE l_abs_addr = fetch(cpu, mem, 1);
    BYTE h_abs_addr = fetch(cpu, mem, 1);

    WORD addr = assemble_pc(l_abs_addr, h_abs_addr);

    BYTE data = r_mem(mem, addr);

    if(--data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0xF0) >> 8;
    w_mem(mem, addr, data);
}

/*
    IMMEDIATE ADDRESSING MODE 
    -------------------------
*/


/* LDY # : 0xA0 */
void ldy_im(Cpu* cpu, Memory* mem)
{
    BYTE data = fetch(cpu, mem, 1);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;
    cpu->y_reg = data;
}

/* LDX #: 0xA2 */
void ldx_im(Cpu* cpu, Memory* mem)
{
    BYTE data = fetch(cpu, mem, 1);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;
    cpu->x_reg = data;
}

/* LDA #: 0xA9 */
void lda_im(Cpu* cpu, Memory* mem)
{
    BYTE data = fetch(cpu, mem, 1);

    if(data == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = (data & 0x80) >> 8;
    cpu->a_reg = data;
}

/* CMP # : 0xC9 */
void cmp_im(Cpu* cpu, Memory* mem)
{
    BYTE data = fetch(cpu, mem, 1);

    if(cpu->a_reg >= data) {
        cpu->ps_reg.c = 1;
    }
    if(cpu->a_reg == data) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = ((cpu->a_reg + data) & 0xF0) >> 8;
}

/*
    IMPLIED ADDRESSING MODE 
    ------------------------
*/

/* DEX : 0xCA */
void dex(Cpu* cpu)
{
    if(--(cpu->x_reg) == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = ((cpu->x_reg) & 0xF0) >> 8;
}

/* TXA: 0x8A */
void txa(Cpu* cpu)
{
    if(cpu->x_reg == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = ((cpu->x_reg) & 0xF0) >> 8;
    cpu->a_reg = cpu->x_reg;
}

/* TAX: 0xAA */
void tax(Cpu* cpu)
{
    if(cpu->a_reg == 0) {
       cpu->ps_reg.z = 1; 
    }
    cpu->ps_reg.n = ((cpu->a_reg) & 0xF0) >> 8;
    cpu->x_reg = cpu->a_reg;
}

/* TXS: 0x */
void txs(Cpu* cpu)
{
    if(cpu->x_reg == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = ((cpu->x_reg) & 0xF0) >> 8;
    cpu->sp_reg = cpu->x_reg;
}

/* TSX: 0x */
void tsx(Cpu* cpu)
{
    if(cpu->sp_reg == 0) {
        cpu->ps_reg.z = 1;
    }
    cpu->ps_reg.n = ((cpu->sp_reg) & 0xF0) >> 8;
    cpu->x_reg = cpu->sp_reg;
}

// and so on...

