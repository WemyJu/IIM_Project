GXX = g++ -std=c++11

all: Dishes.o Dish1.o Dish2.o Dish3.o Algorithm.o FIFO.o MinProcessingTime.o
	$(GXX) simulate.cpp Dishes.o Dish1.o Dish2.o Dish3.o Algorithm.o FIFO.o MinProcessingTime.o -o simulate

Dishes.o: Dishes.h Dishes.cpp
	$(GXX) -c Dishes.cpp

Dish1.o: Dishes.h Dish1.h Dish1.cpp
	$(GXX) -c Dish1.cpp

Dish2.o: Dishes.h Dish2.h Dish2.cpp
	$(GXX) -c Dish2.cpp

Dish3.o: Dishes.h Dish3.h Dish3.cpp
	$(GXX) -c Dish3.cpp

Algorithm.o: Algorithm.h Algorithm.cpp
	$(GXX) -c Algorithm.cpp

FIFO.o: Algorithm.h FIFO.h FIFO.cpp
	$(GXX) -c FIFO.cpp

MinProcessingTime.o: Algorithm.h MinProcessingTime.h MinProcessingTime.cpp
	$(GXX) -c MinProcessingTime.cpp

clean:
	rm -rf *.o simulate
