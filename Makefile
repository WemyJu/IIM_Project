GXX = g++ -std=c++11

all: Dishes.o Algorithm.o FIFO.o MinProcessingTime.o Machine.o
	$(GXX) simulate.cpp Dishes.o Algorithm.o FIFO.o MinProcessingTime.o Machine.o -o simulate

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

clean:
	rm -rf *.o simulate
