.PHONY: all clean zip

ZADANIA =  zadanie1 zadanie2 zadanie3

all: $(ZADANIA)

CXXFLAGS = -Wall -O2 -march=haswell

$(ZADANIA): % : %.o 
	g++ $^ -o $<

%.o : %.cpp
	g++ -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf *.o $(ZADANIA)

zip:
	zip zadania.zip Makefile *.cpp 
