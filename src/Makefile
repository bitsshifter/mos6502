CC=gcc
CFLAGS=-Wall -Wextra

link:
	$(CC) -o emulator.out main.o cpu.o memory.o ops.o

compile:
	$(CC) main.c -o main.o -c $(CFLAGS)
	$(CC) cpu.c -o cpu.o -c $(CFLAGS)
	$(CC) memory.c -o memory.o -c $(CFLAGS)
	$(CC) ops.c -o ops.o -c $(CFLAGS)

clean:
	rm ./*.o
