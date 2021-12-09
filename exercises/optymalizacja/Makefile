.PHONY: all clean

ZADANIA =  zadanie1 zadanie2 zadanie3

all: $(ZADANIA)

CXXFLAGS = -Wall -O2 -std=c++11

$(ZADANIA): % : %.o %.ao
	g++ $(CXXFLAGS) $^ -o $<

%.o : %.cpp
	g++ $(CXXFLAGS) -c  $< -o $@

%.ao : %.asm
	nasm  $< -o $@
#	nasm -felf32  $< -o $@

clean:
	rm -rf *.o *.ao $(ZADANIA)

zip:
	zip zadania.zip Makefile *.cpp *.asm
