//
// IIM project
// MinProcessingTime.cpp
// Created by Wemy Ju on 21/07/2015.
//

#include "MinProcessingTime.h"

MinProcessingTime::MinProcessingTime(vector<Dishes*> oriOrder, int n, int m){
    order = oriOrder;
    num = n;
    clock = 0;
    totalWaiting = 0;
    machine = m;
    timer = new int[machine+1];
    memset(timer, 0, (machine+1)*sizeof(int));
}

MinProcessingTime::~MinProcessingTime(){
    delete [] timer;
}

vector<Dishes*> MinProcessingTime::setOrder(){
    bool *dealed = new bool [num];
    memset(dealed, true, num);
    sort(order.begin(), order.end(), MinProcessingTime::TpCmp);
    int i(0);
    while(i<num){
        for(int k=1; k<=machine && i<num; k++){
            if(clock>=timer[k]){
                bool deal(false);
                for(int j=0; j<num; j++){
                    if(dealed[j] && timer[k] >= order[j]->getTimeR()){
                        dealed[j] = false;
                        order[j]->setMachineNo(k);
                        order[j]->setTimeS(timer[k]);
                        order[j]->setTimeP(order[j]->getDishNo(), k);
                        order[j]->setTimeC(order[j]->getTimeS() + order[j]->getTimeP());
                        order[j]->setTimeW(order[j]->getTimeC() - order[j]->getTimeR());
                        timer[k]+=order[j]->getTimeP();
                        totalWaiting += order[j]->getTimeW();
                        deal = true;
                        break;
                    }
                }
                if(deal) 
                    i++;
                else
                    timer[k]++;
                if(timer[k]>completeTime)
                    completeTime = timer[k];
            }
        }
        clock++;
    }
    delete [] dealed;

    sort(order.begin(), order.end(), MinProcessingTime::TsCmp);

    return order;
}

bool MinProcessingTime::TpCmp(Dishes* a, Dishes* b){
    if(a->getTimeP() != b->getTimeP())
        return a->getTimeP() < b->getTimeP();
    else
        return a->getTimeR() < b->getTimeR();
}

bool MinProcessingTime::TsCmp(Dishes* a, Dishes* b){
    if(a->getTimeS() != b->getTimeS())
        return a->getTimeS() < b->getTimeS();
    else if(a->getTimeP() != b->getTimeP())
        return a->getTimeP() < b->getTimeP();
    else
        return a->getMachine() < b->getMachine();
        
}

void MinProcessingTime::printResult(){
    cout << "Using Min Processing Time\n";
    Algorithm::getResult(order);
}
