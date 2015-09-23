//
// IIM project
// MinProcessingTime.cpp
// Created by Wemy Ju on 21/07/2015.
//

#include "MinProcessingTime.h"

MinProcessingTime::MinProcessingTime(vector<Dishes> oriOrder, int n, int m){
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

vector<Dishes> MinProcessingTime::setOrder(){
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
            if(machineTpOrder[j][i].getTimeC() > 0){
                order[i] = machineTpOrder[j][i];
                break;
            }
        }
    delete [] dealed;

    return order;
}

bool MinProcessingTime::TpCmp(Dishes a, Dishes b){
    if(a.getTimeP() != b.getTimeP())
        return a.getTimeP() < b.getTimeP();
    else
        return a.getTimeR() < b.getTimeR();
}

bool MinProcessingTime::TsCmp(Dishes a, Dishes b){
    if(a.getTimeS() != b.getTimeS())
        return a.getTimeS() < b.getTimeS();
    else if(a.getTimeP() != b.getTimeP())
        return a.getTimeP() < b.getTimeP();
    else
        return a.getMachineNo() < b.getMachineNo();
        
}

bool MinProcessingTime::DishNoCmp(Dishes a, Dishes b){
    return a.getDishNo() < b.getDishNo();
}

void MinProcessingTime::printResult(){
    cout << "Using Min Processing Time\n";
    Algorithm::getResult(order);
}
