//
// IIM project
// GA.cpp
// Created by Wemy Ju on 28/08/2015.
//

#include "GA.h"

GA::GA(int m, int n){
    p1 = par1;
    p2 = par2;
    num = n;
    machine = m;
    totalWaiting = 0;
    completeTime = 0;
    order.clear();
    init();
}

GA::~GA(){};

void GA::init(){ 
    sort(p1.begin(), p1.end(), GA::initSort);
    sort(p2.begin(), p2.end(), GA::initSort);
   
    Dishes dish;
    dish.setMachineNo(0);
    vector<Dishes>::iterator it;
    int i;
    for(it=p1.begin(), i=1; i<=machine; i++, it++){
        while(it->getMachineNo() == i) it++;
        it = p1.insert(it, dish);
    }
    for(it=p2.begin(), i=1; i<=machine; i++, it++){
        while(it->getMachineNo() == i) it++;
        it = p2.insert(it, dish);
    }
    num += machine;
}

bool GA::initSort(Dishes a, Dishes b){
    if(a.getMachineNo() != b.getMachineNo())
        return a.getMachineNo() < b.getMachineNo();
    else
        return a.getTimeS() < b.getTimeS();
}

vector<Dishes> GA::setOrder(){
    crossOver();
    //mutation();

    vector<Dishes>::iterator it=order.begin();
    int timer;
    for(int i=1; i<=machine; i++){
        timer = 0;
        while(it->getMachineNo()!=0 && it!=order.end()){
            it->setMachineNo(i);
            while(timer < it->getTimeR()) timer++;
            it->setTimeS(timer);
            timer += it->getTimeP();
            it->setTimeC(timer);
            it->setTimeW(it->getTimeC() - it->getTimeR());
            totalWaiting += it->getTimeW();
            it++;
        }
        it = order.erase(it);
        if(timer > completeTime)
            completeTime = timer;
    }
    num-=machine;

    return order;
}

void GA::crossOver(){
    vector<Dishes>::iterator it=p2.begin();
    vector<Dishes>::iterator it2;
    bool *dealed = new bool [num+1];
    memset(dealed, false, num+1);
    
    for(int count=0; count<machine-1; count++, it++)
        while(it->getMachineNo()!=0) it++;

    for( ; it!=p2.end(); it++){
        order.push_back(*it);
        if(it->getMachineNo()!=0)
            dealed[it->getNo()] = true;
    }

    for(it=p1.begin(), it2=order.begin(); it!=p1.end(); it++, it2++){
        if(it->getMachineNo()==0)
            it2 = order.insert(it2, *it);
        else
            if(dealed[it->getNo()] == false)
                it2 = order.insert(it2, *it);
    }
    //Algorithm::getResult(order);
}

void GA::mutation(){
    int first,second;
    srand(time(NULL));

    for(int i=0; i<15; i++){
        first = rand()%num+1;
        second = rand()%num+1;
        swap(first, second);
    }
}

void GA::swap(int first, int second){
    Dishes temp = order[first];
    order[second] = order[first];
    order[first] = temp;
}

void GA::printResult(){
    sort(order.begin(), order.end(), resultSort);
    cout << "Using Genetic Algorithm\n";
    Algorithm::getResult(order);
}

bool GA::resultSort(Dishes a, Dishes b){
    if(a.getTable() != b.getTable())
        return a.getTable() < b.getTable();
    else
        return a.getTimeS() < b.getTimeS();
}
