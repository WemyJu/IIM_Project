//
// IIM project
// simulate.cpp
// Created by Wemy Ju on 16/07/2015.
//

#include <iostream>
#include "Dishes.h"
#include "Machine.h"
#include "Algorithm.h"
#include "FIFO.h"
#include "MinProcessingTime.h"
#include "GA.h"

using namespace std;

int main(){
    vector<Dishes> order, p1, p2;
    int numOfOrder(0), machine(0), dish(0);

    Machine::setMachine(machine, dish);
    //Machine::printProcessing();
    Algorithm::initOrder(order, numOfOrder, dish);
    
    FIFO fifo(order, numOfOrder, machine);
    p1 = fifo.setOrder();
    fifo.printResult();
    
    MinProcessingTime minTp(order, numOfOrder, machine);
    p2 = minTp.setOrder();
    minTp.printResult();
    
    GA ga(p1, p2, numOfOrder, machine);
    ga.setOrder();
    ga.printResult();

    Dishes::deleteTp();
}
