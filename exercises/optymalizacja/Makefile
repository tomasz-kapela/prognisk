.PHONY: all clean

ZADANIA =  zadanie1 zadanie2 zadanie3

PROGRAMS = $(patsubst %,%.exe,$(ZADANIA))

all: $(PROGRAMS)

CXXFLAGS = -Wall -O2 -std=c++11 -m32

$(PROGRAMS): %.exe : %.o %.ao
	g++ $(CXXFLAGS) $^ -o $@

zadanie2sol.exe: zadanie2.o zadanie2_sol.o
	g++ $(CXXFLAGS) $^ -o $@

%.o : %.cpp
	g++ $(CXXFLAGS) -c  $< -o $@

%.ao : %.asm
#	nasm  $< -o $@
	nasm -felf32  $< -o $@

clean:
	rm -rf *.o *.ao $(PROGRAMS) zadanie2sol.exe

zip:
	zip zadania.zip Makefile *.cpp *.asm *.h
