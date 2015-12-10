//
// IIM project
// MinProcessingTime.cpp
// Created by Wemy Ju on 21/07/2015.
//

#include "MinProcessingTime.h"

MinProcessingTime::MinProcessingTime(int m, int n){
    num = n;
    totalWaiting = 0;
    completeTime = 0;
    machine = m;
    order.clear();
    result.clear();
    timer = new int[machine+1];
    memset(timer, 0, (machine+1)*sizeof(int));

    dealed = new bool [num];
    memset(dealed, false, num*sizeof(bool));

    machineTpOrder.clear();
    machineTpOrder.reserve(machine+1);
    vector<Dishes> temp;
    machineTpOrder.push_back(temp);
    for(int i=1; i<=machine; i++){
        machineTpOrder.push_back(temp);
        machineTpOrder[i].clear();
    }
}

MinProcessingTime::~MinProcessingTime(){
    delete [] timer;
    delete [] dealed;
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

void MinProcessingTime::addOrder(int timer, Dishes newDish){
    for(int i=1; i<=machine; i++){
        newDish.setTimeP(newDish.getDishNo(), i);
        machineTpOrder[i].insert(machineTpOrder[i].end(), newDish); 
        sort(machineTpOrder[i].begin(), machineTpOrder[i].end(), TpCmp);
    }
}

bool MinProcessingTime::checkSchedule(int clock){
    if(result.size()==num)
        return true;
    for(int i=1; i<=machine; i++){
        if(clock >= timer[i]){
            bool deal(false);
            if(!machineTpOrder[i].empty()){
                for(int j=0; j<machineTpOrder[i].size(); j++){
                    if(!dealed[machineTpOrder[i][j].getNo()]){
                        if(clock>=machineTpOrder[i][j].getTimeR()){
                            dealed[machineTpOrder[i][j].getNo()] = true;
                            machineTpOrder[i][j].setMachineNo(i);
                            machineTpOrder[i][j].setTimeS(clock);
                            machineTpOrder[i][j].setTimeC(machineTpOrder[i][j].getTimeS()+machineTpOrder[i][j].getTimeP());
                            machineTpOrder[i][j].setTimeW(machineTpOrder[i][j].getTimeC() - machineTpOrder[i][j].getTimeR());
                            timer[i]+=machineTpOrder[i][j].getTimeP();
                            totalWaiting += machineTpOrder[i][j].getTimeW();
                            deal = true;
                            result.insert(result.end(), machineTpOrder[i][j]);
                            break;
                        }
                    }
                    else{
                        vector<Dishes>::iterator it = machineTpOrder[i].begin()+j;
                        machineTpOrder[i].erase(it);
                    }
                }
            }
            if(!deal)
                timer[i]++;
        }
    }
    for(int i=1; i<=machine; i++)
        if(timer[i]>completeTime)
            completeTime = timer[i];

    return false;
}

void MinProcessingTime::printResult(){
    cout << "Using Min Processing Time\n";
    Algorithm::getResult(result);
}
