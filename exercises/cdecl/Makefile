.PHONY: all clean zip

PROGRAMS = c_asm suma
# zadanie1 zadanie2 zadanie3

all: $(PROGRAMS)

c_asm: c_asm.asm
	nasm -o c_asm.o -felf c_asm.asm
	gcc -m32 -no-pie c_asm.o -o c_asm

suma:  main.c suma.asm
	nasm -felf32 suma.asm -o suma.o
	gcc -m32 -no-pie -o main.o -c main.c
	gcc -m32 -no-pie main.o suma.o -o suma

clean:
	rm -rf *.o *.ao $(PROGRAMS)

zip:
	zip cdecl.zip Makefile *.c *.asm