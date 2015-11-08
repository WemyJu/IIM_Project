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
    p1.clear();
    p2.clear();
    gaTimer = new int [machine+1];
    memset(gaTimer, 0, (machine+1)*sizeof(int));
    numToMutate = 0;
    srand(time(NULL));
}

GA::GA(){
    totalWaiting = completeTime = 2147483647; // int max     
};

GA::~GA(){};

bool GA::initSort(Dishes a, Dishes b){
    if(a.getMachineNo() != b.getMachineNo())
        return a.getMachineNo() < b.getMachineNo();
    else
        return a.getTimeS() < b.getTimeS();
}

void GA::operator=(GA ga){
    num = ga.num;
    machine = ga.machine;
    result = ga.result;
    totalWaiting = ga.totalWaiting;
    completeTime = ga.completeTime;
}

void GA::renew(){
    totalWaiting = 0;
    completeTime = 0;
    order.clear();
    result.clear();
    p1.clear();
    p2.clear();
    memset(gaTimer, 0, (machine+1)*sizeof(int));
}

void GA::addOrder(int timer, Dishes newDish){
    order.insert(order.end(), newDish);
    p1 = fifo(timer, order);
    p2 = minProcess(timer, order);
    sort(p1.begin(), p1.end(), GA::initSort);
    sort(p2.begin(), p2.end(), GA::initSort);
    crossOver();
    mutation();
}

bool GA::checkSchedule(int clock){
    if(numToMutate > 0){
        for(; numToMutate>0; numToMutate--){
            int range = order.size();
            int first = rand()%range;
            int second = rand()%range;
            if(first != second)
                swap(first, second);
        }

        checkOrder(clock);
    }

    for(int i=1; i<=machine; i++){
        if(clock >= gaTimer[i]){
            vector<Dishes>::iterator it;
            for(it=order.begin(); it!=order.end(); it++){
                bool match(false);
                if(it->getMachineNo() == i){
                    match = true;
                    if(clock >= it->getTimeR()){
                        Dishes dish = (*it);
                        dish.setTimeS(clock);
                        dish.setMachineNo(i);
                        dish.setTimeP(dish.getDishNo(), i);
                        dish.setTimeC(dish.getTimeS()+dish.getTimeP());
                        dish.setTimeW(dish.getTimeC()-dish.getTimeR());
                        gaTimer[i]=dish.getTimeC();
                        totalWaiting += dish.getTimeW();
                        if(dish.getTimeC() > completeTime)
                            completeTime = dish.getTimeC();
                        it = order.erase(it);
                        result.insert(result.end(), dish);
                    }
                }
                if(match)
                    break;
            }
        }
    }
    return order.empty();
}

void GA::crossOver(){
    vector<Dishes>::iterator it=order.begin();
    bool *dealed = new bool [num+1];
    memset(dealed, false, num+1);
    int usedNum(0), pastMachine(1);
    
    order.clear();

    for(int i=0; i<p2.size(); i++)
        if(p2[i].getMachineNo()==machine){
            order.push_back(p2[i]);
            dealed[p2[i].getNo()] = true;
        }

    for(int i=0; i<p1.size(); i++){
        if(p1[i].getMachineNo()==pastMachine){
            if(!dealed[p1[i].getNo()]){
                it = order.insert(it, p1[i]);
                it++;
                dealed[p1[i].getNo()] = true;
            }
            else
                usedNum++;
        }
        else{
            if(usedNum>0)
                usedNum--;
            else
                pastMachine++;
            if(!dealed[p1[i].getNo()]){
                p1[i].setMachineNo(pastMachine);
                it = order.insert(it, p1[i]);
                it++;
                dealed[p1[i].getNo()] = true;
            }
            else
                usedNum++;
        }
    }
}

void GA::mutation(){
    int first, second;
    int change = rand()%100+1;
    if(change<50)
        numToMutate++;
}

void GA::swap(int first, int second){
    Dishes temp = order[first];
    int tempMachineNo = order[second].getMachineNo();
    order[first] = order[second];
    order[first].setMachineNo(temp.getMachineNo());
    order[second] = temp;
    order[second].setMachineNo(tempMachineNo);
}

void GA::checkOrder(int clock){
    int machineNo(1);

    for(int i=1; i<order.size(); i++){
        if(order[i].getMachineNo() == machineNo && order[i-1].getMachineNo() == machineNo){
            if(order[i].getTimeR() > clock && order[i].getTimeR() > order[i-1].getTimeR())
                swap(i, i-1);
        }
        else
            machineNo++;
    }
}

void GA::printResult(){
    sort(order.begin(), order.end(), resultSort);
    cout << "Using Genetic Algorithm\n";
    Algorithm::getResult(result);
}

bool GA::resultSort(Dishes a, Dishes b){
    if(a.getTable() != b.getTable())
        return a.getTable() < b.getTable();
    else
        return a.getTimeS() < b.getTimeS();
}

vector<Dishes> GA::fifo(int clock, vector<Dishes> order_for_fifo){
    sort(order_for_fifo.begin(), order_for_fifo.end(), GA::firstComeCmp);
    int i(0);
    int *timer = new int [machine+1];
    for(int i=0; i<=machine; i++)
        timer[i] = clock;
    while(i<order_for_fifo.size()){
        for(int j=1; j<=machine && i<order_for_fifo.size(); j++){
            if(clock >= timer[j]){
                if(timer[j] >= order_for_fifo[i].getTimeR()){
                    order_for_fifo[i].setTimeP(order_for_fifo[i].getDishNo(), j);
                    order_for_fifo[i].setMachineNo(j);
                    order_for_fifo[i].setTimeS(timer[j]);
                    order_for_fifo[i].setTimeC(order_for_fifo[i].getTimeS() + order_for_fifo[i].getTimeP());
                    order_for_fifo[i].setTimeW(order_for_fifo[i].getTimeC() - order_for_fifo[i].getTimeR());
                    timer[j] += order_for_fifo[i].getTimeP();
                    i++;
                }
                else
                    timer[j]++;
            }
        }
        clock++;
    }
    
    return order_for_fifo;
}

bool GA::firstComeCmp(Dishes a, Dishes b){
    return a.getTimeR() < b.getTimeR();
}

vector<Dishes> GA::minProcess(int clock, vector<Dishes> order_for_mp){
    int size = order_for_mp.size();
    bool *dealed = new bool [num];
    memset(dealed, true, num);
    for(int i = 0; i<order_for_mp.size(); i++)
        order_for_mp[i].setMachineNo(0);
    
    int *timer = new int [machine+1];
    for(int i=0; i<=machine; i++)
        timer[i] = clock;
    
    vector<vector<Dishes>> machineTpOrder(machine+1);
    for(int i=1; i<=machine; i++){
        machineTpOrder[i].clear();
        machineTpOrder[i] = order_for_mp;
        for(int j=0; j<order_for_mp.size(); j++)
            machineTpOrder[i][j].setTimeP(machineTpOrder[i][j].getDishNo(), i);
        sort(machineTpOrder[i].begin(), machineTpOrder[i].end(), GA::TpCmp);
    }
   
    int i(0);
    while(i<order_for_mp.size()){
        for(int k=1; k<=machine && i<order_for_mp.size(); k++){
            if(clock>=timer[k]){
                bool deal(false);
                for(int j=0; j<order_for_mp.size(); j++){
                    if(dealed[machineTpOrder[k][j].getNo()-1] && timer[k] >= machineTpOrder[k][j].getTimeR()){
                        dealed[machineTpOrder[k][j].getNo()-1] = false;
                        machineTpOrder[k][j].setMachineNo(k);
                        machineTpOrder[k][j].setTimeS(timer[k]);
                        machineTpOrder[k][j].setTimeC(machineTpOrder[k][j].getTimeS() + machineTpOrder[k][j].getTimeP());
                        machineTpOrder[k][j].setTimeW(machineTpOrder[k][j].getTimeC() - machineTpOrder[k][j].getTimeR());
                        timer[k]+=machineTpOrder[k][j].getTimeP();
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
        sort(machineTpOrder[i].begin(), machineTpOrder[i].end(), dishNoCmp);
    sort(order.begin(), order.end(), dishNoCmp);
    
    for(int i=0; i<order_for_mp.size(); i++)
        for(int j=1; j<=machine; j++){
            if(machineTpOrder[j][i].getMachineNo() > 0 && machineTpOrder[j][i].getMachineNo() <= machine){
                order_for_mp[i] = machineTpOrder[j][i];
                break;
            }
        }
    
    delete [] dealed;
    
    return order_for_mp;
}

bool GA::dishNoCmp(Dishes a, Dishes b){
    return a.getDishNo() < b.getDishNo();
}

bool GA::TpCmp(Dishes a, Dishes b){
    if(a.getTimeP() != b.getTimeP())
        return a.getTimeP() < b.getTimeP();
    else
        return a.getTimeR() < b.getTimeR();
}
