//
// IIM project
// MinProcessingTime.cpp
// Created by Wemy Ju on 21/07/2015.
//

#include "MinProcessingTime.h"

MinProcessingTime::MinProcessingTime(vector<Dishes*> oriOrder, int n){
    order = oriOrder;
    num = n;
    timer = 0;
    totalWaiting = 0;
}

MinProcessingTime::~MinProcessingTime(){}

void MinProcessingTime::setOrder(){
    bool *dealed = new bool [num];
    memset(dealed, true, num);
    sort(order.begin(), order.end(), MinProcessingTime::TpCmp);
    int i(0);
    while(i<num){
        bool deal(false);
        for(int j=0; j<num; j++)
            if(dealed[j] && timer >= order[j]->getTimeR()){
                dealed[j] = false;
                order[j]->setTimeS(timer);
                order[j]->setTimeC(order[j]->getTimeS() + order[j]->getTimeP());
                order[j]->setTimeW(order[j]->getTimeC() - order[j]->getTimeR());
                timer+=order[j]->getTimeP();
                totalWaiting += order[j]->getTimeW();
                deal = true;
                break;
            }
        if(deal) 
            i++;
        else
            timer++;
        completeTime = timer;
    }
    delete [] dealed;
    
    sort(order.begin(), order.end(), MinProcessingTime::TsCmp);
}

bool MinProcessingTime::TpCmp(Dishes* a, Dishes* b){
    if(a->getTimeP() != b->getTimeP())
        return a->getTimeP() < b->getTimeP();
    else
        return a->getTimeR() < b->getTimeR();
}

bool MinProcessingTime::TsCmp(Dishes* a, Dishes* b){
    return a->getTimeS() < b->getTimeS();
}

void MinProcessingTime::printResult(){
    cout << "Using Min Processing Time\n";
    Algorithm::getResult(order);
}
