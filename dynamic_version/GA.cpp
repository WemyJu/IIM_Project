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
}

GA::~GA(){};

void GA::init(){ 
    sort(p1.begin(), p1.end(), GA::initSort);
    sort(p2.begin(), p2.end(), GA::initSort);
   
   /* Dishes dish;
    dish.setMachineNo(0);
    vector<Dishes>::iterator it;
    int i;
    
    for(it=p1.begin(), i=1; i<=machine; i++, it++){
        while(it!= p1.end() && it->getMachineNo() == i){
            
            //cout << it->getNo() << " " << it->getMachineNo() <<  endl;
            it++;
        }
        it = p1.insert(it, dish);
    }
*/
    int tempnum = num;
    num = p1.size();
    cout << "p1\n";
    Algorithm::getResult(p1);
    //cout << "after p1\n";

   /* for(it=p2.begin(), i=1; i<=machine; i++, it++){
        while(it!=p2.end() && it->getMachineNo() == i){
            //cout << it->getNo() << " " << it->getMachineNo() <<  endl;
            it++;
        }
        it = p2.insert(it, dish);
    }*/
    number = order.size()+machine;


    num = p2.size();
    cout << "p2\n";
    Algorithm::getResult(p2);
    num = tempnum;
}

bool GA::initSort(Dishes a, Dishes b){
    if(a.getMachineNo() != b.getMachineNo())
        return a.getMachineNo() < b.getMachineNo();
    else
        return a.getTimeS() < b.getTimeS();
}

void GA::addOrder(int timer, Dishes newDish){
    //cout << "in addOrder\n";
    order.insert(order.end(), newDish);
    p1 = fifo(timer, order);
    p2 = minProcess(timer, order);
    init();
    //crossOver();
    //mutation();
}

vector<Dishes> GA::setOrder(){
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

bool GA::checkSchedule(int clock){
    for(int i=1; i<=machine; i++){
        //cout << "clock = " << clock << "  i = " << i << " t = " << gaTimer[i] << endl;
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
    cout << "in minProcess\n";
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
                cout << "c= " << clock << "t[" << k << "]= "<< timer[k] << endl;
                bool deal(false);
                for(int j=0; j<order_for_mp.size(); j++){
                    if(dealed[machineTpOrder[k][j].getNo()-1] && timer[k] >= machineTpOrder[k][j].getTimeR()){
                        cout << "k= "<<k << " j=" << j << endl;
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
                cout << machineTpOrder[1][i].getMachineNo() << " " << machineTpOrder[2][i].getMachineNo() << " " << machineTpOrder[3][i].getMachineNo() << endl;
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
