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

bool timeRCmp(Dishes a, Dishes b){
    return a.getTimeR() < b.getTimeR();
}

int main(){
    vector<Dishes> order, fifoResult, minProResult, GAResult, p1, p2;
    int numOfOrder(0), machine(0), clock(0), numOfDish(0);
    bool fifoEnd(false), minProEnd(false), GAEnd(false); 

    Machine::setMachine(machine, numOfDish);
    //Machine::printProcessing();
    Algorithm::initOrder(order, numOfOrder, numOfDish);
    sort(order.begin(), order.end(), timeRCmp);
   
    FIFO fifo(machine, numOfOrder);
    MinProcessingTime minPro(machine, numOfOrder);
    GA ga(machine, numOfOrder);
    while(!fifoEnd || !minProEnd || !GAEnd || !order.empty()){
        while(clock >= order.begin()->getTimeR() && !order.empty()){
            Dishes dish = *(order.begin());
            fifo.addOrder(clock, dish);
            minPro.addOrder(clock, dish);
            ga.addOrder(clock, dish);
            order.erase(order.begin());
        }
        fifoEnd = fifo.checkSchedule(clock);
        minProEnd = minPro.checkSchedule(clock);
        GAEnd = ga.checkSchedule(clock);
     //   GAEnd = true;
        clock++;
    }
     fifo.printResult();
     minPro.printResult();
     ga.printResult();

    Dishes::deleteTp();
}
