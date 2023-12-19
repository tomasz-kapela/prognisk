
COPY = copy_rep copy_loop copy_movsq copy_forward copy_backward

$(COPY:%=%.exe): % : copy.asm copy.c
	gcc -DCOPY=$(@:%.exe=%) -c copy.c -o copy.o
	nasm -felf64 copy.asm -o copy.a
	gcc copy.o copy.a -o $@

run_copy: $(COPY:%=%.exe) $(COPY:%=%.run)


DEPENDANCY = SIMPLE PREFETCH VECTOR
DCPP = -O0

$(DEPENDANCY:%=suma_%.exe): suma_dependancy.cpp
	g++ ${DCPP} -mavx2 -D$(@:suma_%.exe=%) suma_dependancy.cpp -o $@

run_dependancy: $(DEPENDANCY:%=suma_%.exe) $(DEPENDANCY:%=suma_%.run)

%.run: %.exe
	./$<
	@echo " -  -  -  -  -  -"

.PHONY: clean
clean:
	rm -f *.exe *.o