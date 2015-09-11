//
// IIM project
// GA.cpp
// Created by Wemy Ju on 28/08/2015.
//

#include "GA.h"

GA(vector<Dishes*> p1, vector<Dishes*> p2, int n, int m){
    order = p1;
    num = n;
    machine = m;
    totalWaiting = INT_MAX;
    completeTime = INT_MAX;
    init(p1, p2);
}

~GA(){};

void init(vector<Dishes*> &p1, vector<Dishes*>p2){ 
    sort(p1.begin(), p1.end(), GA::initSort);
    sort(p2.begin(), p2.end(), GA::initSort);
    
    Dishes* dish = new Dishes;
    dish -> setMachineNo(0);
    vector<Dishes*>::iterator it = p1.begin();
    for(int i=1; i<=machine; i++){
        while(it->getMachine() == machine) it++;
        it = p1.insert(it, dish);
    }
    it = p2.begin();
    for(int i=1; i<=machine; i++){
        while(it->getMachine() == machine) it++;
        it = p2.insert(it, dish);
    }
    num += machine;
}

bool GA::initSort(Dishes* a, Dishes* b){
    if(a->getMachine() != b->getMachine())
        return a->getMachine() < b->getMachine();
    else(a->getTimeS() != b->getTimeS())
        return b->getTimeS() < b->getTimeS();
}
