GXX = g++ -std=c++11

all: Dishes.o Algorithm.o Machine.o FIFO.o MinProcessingTime.o GA.o
	$(GXX) simulate.cpp Dishes.o Machine.o Algorithm.o FIFO.o MinProcessingTime.o GA.o -o simulate

Dishes.o: Dishes.h Dishes.cpp
	$(GXX) -c Dishes.cpp

Algorithm.o: Algorithm.h Algorithm.cpp
	$(GXX) -c Algorithm.cpp

Machine.o: Dishes.h Machine.h Machine.cpp
	$(GXX) -c Machine.cpp

FIFO.o: Algorithm.h FIFO.h FIFO.cpp
	$(GXX) -c FIFO.cpp

MinProcessingTime.o: Algorithm.h MinProcessingTime.h MinProcessingTime.cpp
	$(GXX) -c MinProcessingTime.cpp

GA.o: Algorithm.h GA.h GA.cpp
	$(GXX) -c GA.cpp

clean:
	rm -rf *.o simulate
