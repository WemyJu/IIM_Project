//
// IIM project
// GA.cpp
// Created by Wemy Ju on 28/08/2015.
//

#include "GA.h"

GA::GA(int m, int n){
    num = n;
    machine = m;
    totalWaiting = 0;
    completeTime = 0;
    order.clear();
    result.clear();
    timer = new int [machine+1];
    memset(timer, 0, (machine+1)*sizeof(int));
    p1.clear();
    p2.clear();

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

void GA::addOrder(int timer, Dishes newDish){
    order.insert(order.end(), newDish);
    sort(p1.begin(), p1.end(), firstComeCmp);
    p1 = fifo(order);
    p2 = minProcess(order);
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

vector<Dishes> fifo(vector<Dishes> order_for_fifo){
    sort(order_for_fifo.begin(), order_for_fifo.end(), GA::firstComeCmp);
    int i(0);
    while(i<num){
        for(int j=1; j<=machine && i<num; j++){
            if(clock > timer[j]){
                if(timer[j] >= order_for_fifo[i].getTimeR()){
                    order_for_fifo[i].setTimeP(order_for_fifo[i].getDishNo(), j);
                    order_for_fifo[i].setMachineNo(j);
                    order_for_fifo[i].setTimeS(timer[j]);
                    order_for_fifo[i].setTimeC(order_for_fifo[i].getTimeS() + order_for_fifo[i].getTimeP());
                    order_for_fifo[i].setTimeW(order_for_fifo[i].getTimeC() - order_for_fifo[i].getTimeR());
                    timer[j] += order_for_fifo[i].getTimeP();
                    totalWaiting += order_for_fifo[i].getTimeW();
                    i++;
                }
                else
                    timer[j]++;
            }
        }
        clock++;
    }
    
    return order;
}

bool GA::firstComeCmp(Dishes a, Dishes b){
    return a.getTimeR() < b.getTimeR();
}

vector<Dishes> minProcess(vector<Dishes>){
    bool *dealed = new bool [num];
    memset(dealed, true, num);
    
    vector<vector<Dishes>> machineTpOrder(machine+1);
    for(int i=1; i<=machine; i++){
        machineTpOrder[i] = order;
        for(int j=0; j<num; j++)
            machineTpOrder[i][j].setTimeP(machineTpOrder[i][j].getDishNo(), i);
        sort(machineTpOrder[i].begin(), machineTpOrder[i].end(), MinProcessingTime::TpCmp);
    }
    
    int i(0);
    while(i<num){
        for(int k=1; k<=machine && i<num; k++){
            if(clock>=timer[k]){
                bool deal(false);
                for(int j=0; j<num; j++){
                    if(dealed[machineTpOrder[k][j].getNo()-1] && timer[k] >= machineTpOrder[k][j].getTimeR()){
                        dealed[machineTpOrder[k][j].getNo()-1] = false;
                        machineTpOrder[k][j].setMachineNo(k);
                        machineTpOrder[k][j].setTimeS(timer[k]);
                        machineTpOrder[k][j].setTimeC(machineTpOrder[k][j].getTimeS() + machineTpOrder[k][j].getTimeP());
                        machineTpOrder[k][j].setTimeW(machineTpOrder[k][j].getTimeC() - machineTpOrder[k][j].getTimeR());
                        timer[k]+=machineTpOrder[k][j].getTimeP();
                        totalWaiting += machineTpOrder[k][j].getTimeW();
                        deal = true;
                        break;
                    }
                }
                if(deal)
                    i++;
                else
                    timer[k]++;
            }
        }
        clock++;
    }
    
    for(int i=1; i<=machine; i++)
        if(timer[i]>completeTime)
            completeTime = timer[i];
    
    for(int i=1; i<=machine; i++)
        sort(machineTpOrder[i].begin(), machineTpOrder[i].end(), DishNoCmp);
    sort(order.begin(), order.end(), DishNoCmp);
    
    for(int i=0; i<num; i++)
        for(int j=1; j<=machine; j++){
            if(machineTpOrder[j][i].getMachineNo() > 0){
                order[i] = machineTpOrder[j][i];
                break;
            }
        }
    
    delete [] dealed;
    
    return order;
}
