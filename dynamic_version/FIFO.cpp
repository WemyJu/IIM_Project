//
// IIM project 
// FIFO.cpp
// Created by Wemy Ju on 16/07/2015.
//

#include "FIFO.h"

FIFO::FIFO(int m, int n){
    num = n;
    totalWaiting = 0;
    completeTime = 0;
    machine = m;
    order.clear();
    result.clear();
    timer = new int[machine+1];
    memset(timer, 0, (machine+1)*sizeof(int));
}

FIFO::~FIFO(){
    delete[] timer;
}

bool FIFO::firstComeCmp(Dishes a, Dishes b){
    return a.getTimeR() < b.getTimeR();
}

void FIFO::addOrder(int timer, Dishes newDish){
    order.insert(order.end(), newDish);
    sort(order.begin(), order.end(), FIFO::firstComeCmp);
}

bool FIFO::checkSchedule(int clock){
    for(int i=1; i<=machine; i++){
        if(clock >= timer[i] && !order.empty()){
            Dishes dish = *(order.begin());
            dish.setMachineNo(i);
            dish.setTimeS(clock);
            dish.setTimeP(dish.getDishNo(), i);
            dish.setTimeC(dish.getTimeS()+dish.getTimeP());
            dish.setTimeW(dish.getTimeC()-dish.getTimeR());
            if(dish.getTimeC()>completeTime)
                completeTime = dish.getTimeC();
            totalWaiting += dish.getTimeW();
            timer[i] = dish.getTimeC();
            result.insert(result.end(), dish);
            order.erase(order.begin());
        }
    }

    return order.empty();
}

void FIFO::printResult(){
    cout << "Using FIFO\n";
    Algorithm::getResult(result);
}

vector<Dishes> FIFO::getResult(){
    return result;
}
