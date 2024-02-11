CXXFLAGS =

CXXINCLUDES = .

main.exe: main.o 
	g++ $(CXXFLAGS) main.o -o main.exe

main.o: main.cpp set.hpp
	g++ $(CXXFLAGS) -I$(CXXINCLUDES) -c main.cpp -o main.o

.PHONY: clean doc all

clean:
	rm *.o *.exe

doc:
	doxygen

all: main.exe doc
