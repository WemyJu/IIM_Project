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
    gaTimer = new int [machine+1];
    memset(gaTimer, 0, (machine+1)*sizeof(int));
    srand(time(NULL));
}

GA::GA(){
    totalWaiting = completeTime = MAXINT;    
};

GA::~GA(){
    delete[] gaTimer;
};

bool GA::initSort(Dishes a, Dishes b){
    if(a.getMachineNo() != b.getMachineNo())
        return a.getMachineNo() < b.getMachineNo();
    else
        return a.getTimeS() < b.getTimeS();
}

bool GA::resultSort(Dishes a, Dishes b){
    if(a.getTable() != b.getTable())
        return a.getTable() < b.getTable();
    else
        return a.getTimeS() < b.getTimeS();
}

bool GA::firstComeCmp(Dishes a, Dishes b){
    return a.getTimeR() < b.getTimeR();
}

bool GA::dishNoCmp(Dishes a, Dishes b){
    return a.getNo() < b.getNo();
}

bool GA::TpCmp(Dishes a, Dishes b){
    if(a.getTimeP() != b.getTimeP())
        return a.getTimeP() < b.getTimeP();
    else
        return a.getTimeR() < b.getTimeR();
}

bool GA::machineCmp(Dishes a, Dishes b){
    if(a.getMachineNo() != b.getMachineNo())
        return a.getTimeS() < b.getTimeS();
    else
        return a.getMachineNo() < b.getMachineNo();
}

void GA::operator=(GA ga){
    num = ga.num;
    machine = ga.machine;
    result = ga.result;
    totalWaiting = ga.totalWaiting;
    completeTime = ga.completeTime;
}

void GA::addOrder(Dishes newDish){
    order.insert(order.end(), newDish);
}

void GA::findBest(int clock){
    int localWaiting(MAXINT), TwBestChoice(-1);
    int *tempTimer = new int [machine+1];

    for(int i=0; i<childNum; i++){
        for(int j=1; j<=machine; j++)
            tempTimer[j] = gaTimer[j];

        int k(0), Tw(0);
        int m;
        for(int j=0; j<c[i].size(); j++){
            m = c[i][j].getMachineNo();
            if(tempTimer[m]<c[i][j].getTimeR())
                tempTimer[m] = c[i][j].getTimeR();
            c[i][j].setTimeS(tempTimer[m]);
            c[i][j].setTimeP(c[i][j].getDishNo(), m);
            Tw += tempTimer[m] + c[i][j].getTimeP() - c[i][j].getTimeR();
            tempTimer[m] += c[i][j].getTimeP();
        }

        if(c[i].size() > 0 && Tw < localWaiting){
            TwBestChoice = i;
            localWaiting = Tw;
        }
    }

    order = c[TwBestChoice];
    delete[] tempTimer;
}

void GA::findBetter(int clock){
    int *tempTimer = new int [machine+1];
    CHILDINFO childInfo;
    priority_queue< CHILDINFO, vector<CHILDINFO>, chooseGenerations > childTw;

    for(int i=0; i<childNum; i++){
        for(int m=1; m<=machine; m++)
            tempTimer[m] = gaTimer[m];
        int k(0), Tw(0);
        int m;
        for(int j=0; j<c[i].size(); j++){
            m = c[i][j].getMachineNo();
            if(tempTimer[m]<c[i][j].getTimeR())
                tempTimer[m] = c[i][j].getTimeR();
            c[i][j].setTimeS(tempTimer[m]);
            c[i][j].setTimeP(c[i][j].getDishNo(), m);
            Tw += tempTimer[m] + c[i][j].getTimeP() - c[i][j].getTimeR();
            tempTimer[m] += c[i][j].getTimeP();
        }
        if(c[i].size() > 0){
            childInfo.Tw = Tw;
            childInfo.index = i;
            childTw.push(childInfo);
        }
    }

    //cout << "waiting time = " << childTw.top().Tw << " " << childTw.top().index <<  endl;
    for(int i=0; i<childTw.size(); i++){
        childInfo = childTw.top();
        p[i] = c[childInfo.index];
        childTw.pop();
    }

    delete[] tempTimer;
}

void GA::generateChild(int clock){
    childNum = 1225;
    p[0] = fifo(clock, order);
    p[1] = minProcess(clock, order);
    for(int i=2; i<18; i++)
        p[i] = p[0];
    for(int i=18; i<35; i++)
        p[i] = p[1];
    for(int i=2; i<35; i++){
        for(int j=0; j<p[i].size(); j++){
            int first = rand()%p[i].size();
            //int first = j;
            int second = rand()%p[i].size();
            if(first != second){
                Dishes temp = p[i][first];
                int tempMachineNo = p[i][second].getMachineNo();
                p[i][first] = p[i][second];
                p[i][first].setMachineNo(temp.getMachineNo());
                p[i][second] = temp;
                p[i][second].setMachineNo(tempMachineNo);
            }
        }
    } 
    for(int i=0; i<35; i++)
        sort(p[i].begin(), p[i].end(), initSort);
    crossOver();
    mutation();
    for(int i=0; i<100; i++){
        findBetter(clock);
        crossOver();
        mutation();
    }
}

bool GA::checkSchedule(int clock){
    vector<Dishes>::iterator it;
    for(int i=1; i<=machine; i++){
        if(clock >= gaTimer[i]){
            for(it=order.begin(); it!=order.end(); it++){
                bool match(false);
                if(it->getMachineNo() == i){
                    if(clock >= it->getTimeR()){
                        match = true;
                        Dishes dish = (*it);
                        dish.setTimeS(clock);
                        //dish.setTimeP(dish.getDishNo(), i);
                        dish.setTimeC(dish.getTimeS()+dish.getTimeP());
                        dish.setTimeW(dish.getTimeC()-dish.getTimeR());
                        gaTimer[i]=dish.getTimeC();
                        totalWaiting += dish.getTimeW();
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

void GA::printResult(){
    sort(order.begin(), order.end(), resultSort);
    cout << "Using Genetic Algorithm\n";
    Algorithm::getResult(result);
}

void GA::crossOver(){
    vector<Dishes>::iterator it;
    bool *dealed = new bool [num+1];
    int index, usedNum(0), pastMachine(1);

    for(int p1=0; p1<35; p1++){
        for(int p2=0; p2<35; p2++){
            index = p1*35+p2;
            if(p1 == p2){
                c[index] = p[p1];
            }
            else{
                usedNum = 0;
                pastMachine = 1;
                c[index].clear();
                memset(dealed, false, num+1);

                for(int i=0; i<p[p2].size(); i++){
                    if(p[p2][i].getMachineNo() == machine){
                        Dishes dish = p[p2][i];
                        c[index].push_back(dish);
                        dealed[p[p2][i].getNo()] = true;
                    }
                }
                it = c[index].begin();
                for(int i=0; i<p[p1].size(); i++){
                    if(p[p1][i].getMachineNo()==pastMachine){
                        if(!dealed[p[p1][i].getNo()]){
                            Dishes dish = p[p1][i];
                            it = c[index].insert(it, dish);
                            it++;
                            dealed[p[p1][i].getNo()] = true;
                        }
                        else
                            usedNum++;
                    }
                    else{
                        if(!dealed[p[p1][i].getNo()]){
                            if(usedNum>0)
                                usedNum--;
                            else
                                pastMachine++;
                            Dishes dish = p[p1][i];
                            dish.setMachineNo(pastMachine);
                            it = c[index].insert(it, dish);
                            it++;
                            dealed[p[p1][i].getNo()] = true;
                        }
                        else
                            usedNum++;
                    }
                }
            }
        }
    }
    delete [] dealed;
}

void GA::mutation(){
    int index;
    for(int p1=0; p1<35; p1++)
        for(int p2=0; p2<35; p2++){
            index = p1*35+p2;
            if(c[index].size()!=0){
                for(int i=0; i<1; i++){
                    int change = rand()%101;
                    int first = rand()%c[index].size();
                    int second = rand()%c[index].size();
                    if(change<40 && first!=second)
                        swap(first, second, index);
                }
            }
        }
}

void GA::swap(int first, int second, int index){
    Dishes temp = c[index][first];
    int tempMachineNo = c[index][second].getMachineNo();
    c[index][first] = c[index][second];
    c[index][first].setMachineNo(temp.getMachineNo());
    c[index][second] = temp;
    c[index][second].setMachineNo(tempMachineNo);
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
    delete[] timer; 
    return order_for_fifo;
}

vector<Dishes> GA::minProcess(int clock, vector<Dishes> order_for_mp){
    int size = order_for_mp.size();
    bool *dealed = new bool [num+1];
    memset(dealed, true, num+1);
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
                    if(dealed[machineTpOrder[k][j].getNo()] && timer[k] >= machineTpOrder[k][j].getTimeR()){
                        dealed[machineTpOrder[k][j].getNo()] = false;
                        machineTpOrder[k][j].setMachineNo(k);
                        machineTpOrder[k][j].setTimeS(clock);
                        machineTpOrder[k][j].setTimeC(machineTpOrder[k][j].getTimeS() + machineTpOrder[k][j].getTimeP());
                        machineTpOrder[k][j].setTimeW(machineTpOrder[k][j].getTimeC() - machineTpOrder[k][j].getTimeR());
                        timer[k]+=machineTpOrder[k][j].getTimeP();
                        deal = true;
                        break;
                    }
                }
                if(deal){
                    i++;
                }
                else
                    timer[k]++;
            }
        }
        clock++;
    }
    for(int i=1; i<=machine; i++)
        sort(machineTpOrder[i].begin(), machineTpOrder[i].end(), dishNoCmp);
    sort(order_for_mp.begin(), order_for_mp.end(), dishNoCmp);

    for(int i=0; i<order_for_mp.size(); i++)
        for(int j=1; j<=machine; j++){
            if(machineTpOrder[j][i].getMachineNo() > 0 && machineTpOrder[j][i].getMachineNo() <= machine){
                order_for_mp[i] = machineTpOrder[j][i];
                //break;
            }
        }
    delete[] dealed;
    delete[] timer;

    return order_for_mp;
}
