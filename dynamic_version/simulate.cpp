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
    vector<Dishes> order, oriOrder;
    int numOfOrder(0), machine(0), clock(0), numOfDish(0);
    bool fifoEnd(false), minProEnd(false), GAEnd(false); 

    Machine::setMachine(machine, numOfDish);
    //Machine::printProcessing();
    Algorithm::initOrder(order, numOfOrder, numOfDish);
    sort(order.begin(), order.end(), timeRCmp);
    oriOrder = order;

    FIFO fifo(machine, numOfOrder);
    MinProcessingTime minPro(machine, numOfOrder);
    while(!fifoEnd || !minProEnd || !order.empty()){
        while(clock >= order.begin()->getTimeR() && !order.empty()){
            Dishes dish = *(order.begin());
            fifo.addOrder(clock, dish);
            minPro.addOrder(clock, dish);
            order.erase(order.begin());
        }
        fifoEnd = fifo.checkSchedule(clock);
        minProEnd = minPro.checkSchedule(clock);
        clock++;
    }
    fifo.printResult();
    minPro.printResult();


    GA gaMinTw, gaMinTc, ga(machine, numOfOrder);
    order = oriOrder;
    clock = 0;
    bool addDish = false;
    while(!GAEnd || !order.empty()){
        while(clock >= order.begin()->getTimeR() && !order.empty()){
            Dishes dish = *(order.begin());
            ga.addOrder(dish);
            order.erase(order.begin());
            addDish = true;
        }
        if(addDish){
            ga.generateChild(clock);
            ga.findBest(clock);
            addDish = false;
        }
        GAEnd = ga.checkSchedule(clock);
        clock++;
    }
    ga.printResult();
    
    Dishes::deleteTp();
}
