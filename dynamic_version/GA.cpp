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
    numToMutate = 0;
    srand(time(NULL));
}

GA::GA(){
    totalWaiting = completeTime = MAXINT;    
};

GA::~GA(){
    delete [] gaTimer;
};

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

void GA::addOrder(Dishes newDish){
    order.insert(order.end(), newDish);
}

void GA::findBest(int clock){
    int localWaiting(MAXINT), localComplete(MAXINT), TwBestChoice(-1), TcBestChoic(-1);
    int *tempTimer = new int [machine+1];

    for(int i=0; i<childNum; i++){
        for(int j=1; j<=machine; j++)
            tempTimer[j] = gaTimer[j];
        int k(0), Tw(0), Tc(0);
        while(k<c[i].size()){
            for(int j=1; j<=machine && k<c[i].size(); j++){
                if(clock >= tempTimer[j]){
                    if(tempTimer[j] >= c[i][k].getTimeR()){
                        c[i][k].setTimeP(c[i][k].getDishNo(), j);
                        tempTimer[j] += c[i][k].getTimeP();
                        Tw += tempTimer[j] + c[i][k].getTimeP() - c[i][k].getTimeR();
                        k++;
                    }
                    else
                        tempTimer[j]++;
                }
            }
            clock++;
        }
        if(c[i].size() > 0 && localWaiting > Tw){
            localWaiting = Tw;
            TwBestChoice = i;
        }
    }
    //cout << "Best = " << TwBestChoice << endl;
    order = c[TwBestChoice];
    delete [] tempTimer;
}

void GA::generateChild(int clock){
    childNum = 1225;
    p[0] = fifo(clock, order);
    p[1] = minProcess(clock, order);
    for(int i=2; i<26; i++)
        p[i] = p[0];
    for(int i=26; i<50; i++)
        p[i] = p[1];
    for(int i=2; i<50; i++){
        for(int j=0; j<p[i].size(); j++){
            int first = rand()%p[i].size();
            int second = rand()%p[i].size();
            if(first != second){
                Dishes temp = p[j][first];
                int tempMachineNo = p[j][second].getMachineNo();
                p[j][first] = p[j][second];
                p[j][first].setMachineNo(temp.getMachineNo());
                p[j][second] = temp;
                p[j][second].setMachineNo(tempMachineNo);
            }
        }
        sort(p[i].begin(), p[i].end(), initSort);
    }
    for(int i=0; i<50; i++)
        for(int j=i+1; j<50; j++)
            crossOver(i, j);
    for(int i=0; i<childNum; i++)
        mutation(i);
}

bool GA::checkSchedule(int clock){
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

void GA::crossOver(int p1, int p2){
    int index = p1*((50-1)-(p1+1)/2)+p2-1;
    vector<Dishes>::iterator it;
    bool *dealed = new bool [num+1];
    memset(dealed, false, num+1);
    int usedNum(0), pastMachine(1);
    c[index].clear();

    for(int i=0; i<p[p2].size(); i++)
        if(p[p2][i].getMachineNo() == machine){
           c[index].push_back(p[p2][i]);
            dealed[p[p2][i].getNo()] = true;
        }
    it = c[index].begin();
    for(int i=0; i<p[p1].size(); i++){
        if(p[p1][i].getMachineNo()==pastMachine){
            if(!dealed[p[p1][i].getNo()]){
                it = c[index].insert(it, p[p1][i]);
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
                p[p1][i].setMachineNo(pastMachine);
                it = c[index].insert(it, p[p1][i]);
                it++;
                dealed[p[p1][i].getNo()] = true;
            }
            else
                usedNum++;
        }
    }
    
    delete [] dealed;
}

void GA::mutation(int index){
    if(c[index].size()!=0){
        int change = rand()%100+1;
        int first = rand()%c[index].size();
        int second = rand()%c[index].size();
        if(change<50 && first!=second)
        swap(first, second, index);
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

void GA::checkOrder(int clock, int index){
    int machineNo(1);

    for(int i=1; i<c[index].size(); i++){
        if(c[index][i].getMachineNo() == machineNo && c[index][i-1].getMachineNo() == machineNo){
            if(c[index][i].getTimeR() > clock && c[index][i].getTimeR() > c[index][i-1].getTimeR())
                swap(i, i-1, index);
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
    delete [] timer; 
    return order_for_fifo;
}

bool GA::firstComeCmp(Dishes a, Dishes b){
    return a.getTimeR() < b.getTimeR();
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
                        machineTpOrder[k][j].setTimeS(timer[k]);
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
                break;
            }
        }
    delete [] dealed;
    delete [] timer;

    return order_for_mp;
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
