//
// IIM project 
// FIFO.cpp
// Created by Wemy Ju on 16/07/2015.
//

#include "FIFO.h"

FIFO::FIFO(vector<Dishes*> oriOrder, int n, int m){
    order = oriOrder;
    num = n;
    totalWaiting = 0;
    machine = m;
    clock = 0;
    timer = new int[machine+1];
    memset(timer, 0, (machine+1)*sizeof(int));
}

FIFO::~FIFO(){
    delete [] timer;
}

vector<Dishes*> FIFO::setOrder(){
    sort(order.begin(), order.end(), FIFO::firstComeCmp);
    int i(0);
    while(i<num){
        for(int j=1; j<=machine && i<num; j++){
            if(clock > timer[j]){
                if(timer[j] >= order[i]->getTimeR()){
                    order[i]->setTimeP(order[i]->getDishNo(), j);
                    order[i]->setMachineNo(j);
                    order[i]->setTimeS(timer[j]);
                    order[i]->setTimeC(order[i]->getTimeS() + order[i]->getTimeP());
                    order[i]->setTimeW(order[i]->getTimeC() - order[i]->getTimeR());
                    timer[j] += order[i]->getTimeP();
                    totalWaiting += order[i]->getTimeW();
                    i++;
                }
                else
                    timer[j]++;

                if(timer[j] > completeTime)
                    completeTime = timer[j];
            }
        }
        clock++;
    }

    return order;
}

bool FIFO::firstComeCmp(Dishes* a, Dishes* b){
    return a->getTimeR() < b->getTimeR();
}

void FIFO::printResult(){
    cout << "Using FIFO\n";
    Algorithm::getResult(order);
}
