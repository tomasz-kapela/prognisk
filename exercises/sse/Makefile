.PHONY: all clean

ZADANIA =  zadanie1 zadanie2 zadanie3

all: $(ZADANIA)

CXXFLAGS = -Wall -O2

$(ZADANIA): % : %.o %.ao
	g++ $^ -o $<

%.o : %.cpp
	g++ -c $(CXXFLAGS) $< -o $@

%.ao : %.asm
	nasm -felf64  $< -o $@

clean:
	rm -rf *.o *.ao $(ZADANIA)

zip:
	zip zadania.zip Makefile *.cpp *.asm
