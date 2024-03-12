#include "headers/memory.h"
#include "headers/cpu.h"
#include "headers/ops.h"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    Memory mem;
    Cpu cpu;

    init_mem(&mem);
    set_reset_vector(&mem, 0x0200);

    load_program(&mem, "test/a.out");

    reset(&cpu, &mem);

    // Part of testing
    w_mem(&mem, 0x0000, 0x80);
    w_mem(&mem, 0x0001, 0x90);
    w_mem(&mem, 0x0002, 0x0A);

    run(&cpu, &mem);

    return 0;
}
