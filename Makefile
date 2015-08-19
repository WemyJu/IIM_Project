GXX = g++ -std=c++11

all: Dishes.o Algorithm.o FIFO.o MinProcessingTime.o
	$(GXX) simulate.cpp Dishes.o Algorithm.o FIFO.o MinProcessingTime.o -o simulate

Dishes.o: Dishes.h Dishes.cpp
	$(GXX) -c Dishes.cpp

Algorithm.o: Algorithm.h Algorithm.cpp
	$(GXX) -c Algorithm.cpp

FIFO.o: Algorithm.h FIFO.h FIFO.cpp
	$(GXX) -c FIFO.cpp

MinProcessingTime.o: Algorithm.h MinProcessingTime.h MinProcessingTime.cpp
	$(GXX) -c MinProcessingTime.cpp

clean:
	rm -rf *.o simulate
