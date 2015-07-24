//
// IIM project 
// FIFO.cpp
// Created by Wemy Ju on 16/07/2015.
//

#include "FIFO.h"

FIFO::FIFO(vector<Dishes*> oriOrder, int n){
    order = oriOrder;
    num = n;
    timer = 0;
    totalWaiting = 0;
}

FIFO::~FIFO(){}

void FIFO::setOrder(){
    sort(order.begin(), order.end(), FIFO::firstComeCmp);
    for(int i=0; i<num; i++){
        while(true){
            if(timer >= order[i]->getTimeR()){
                order[i]->setTimeS(timer);
                order[i]->setTimeC(order[i]->getTimeS() + order[i]->getTimeP());
                order[i]->setTimeW(order[i]->getTimeC() - order[i]->getTimeR());
                timer += order[i]->getTimeP();
                totalWaiting += order[i]->getTimeW();
                break;
            }
            else
                timer++;
        }
    }
    completeTime = timer;
}

bool FIFO::firstComeCmp(Dishes* a, Dishes* b){
    return a->getTimeR() < b->getTimeR();
}

void FIFO::printResult(){
    cout << "Using FIFO\n";
    Algorithm::getResult(order);
}
