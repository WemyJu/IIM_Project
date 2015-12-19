//
// IIM project
// SA.cpp
// Created by Ruby & Wemy.
//

#include "SA.h"
#include <fstream>

using namespace std;

SA::SA(int m, int n){
    order.clear();
    result.clear();
    num = n;
    machine = m;
    k = 1;
    T=9999;
    loop=0;
    SA_totalWaiting = 2147483647; // INT MAX
    totalWaiting = 0;

    timer = new int [machine+1];
    memset(timer, 0, sizeof(int)*(machine+1));

    vector<Dishes> temp;
    for(int i=0; i<=machine;i++){
        SA_vector.push_back(temp);
        SA_newVector.push_back(temp);
    }
}

void SA::logic(int clock){
    while(loop<100 &&  T<100){
        perturbation(clock);
        acceptance();
    }
}

bool SA::SA_order(Dishes a,Dishes b){
    if(a.getMachineNo()!=b.getMachineNo())
        return a.getMachineNo() < b.getMachineNo();
    else
        return a.getTimeR() < b.getTimeR();
}


bool SA::TrCmp(Dishes a, Dishes b){
    if(a.getTimeR() != b.getTimeR())
        return a.getTimeR() < b.getTimeR();
    else
        return a.getTimeP() < b.getTimeP();
}

bool SA::dishNoCmp(Dishes a, Dishes b){
    return a.getNo() < b.getNo();
}

bool SA::TpCmp(Dishes a, Dishes b){
    if(a.getTimeP() != b.getTimeP())
        return a.getTimeP() < b.getTimeP();
    else
        return a.getTimeR() < b.getTimeR();
}

void SA::compareTW(int &SAT, int &MAT){
    if( MAT > SAT)
        SAT = MAT;
}

bool SA::checkSchedule(int clock){
    for(int i=1; i<=machine; i++)
        if(clock>=timer[i] && !SA_vector[i].empty()){
            if(clock >= SA_vector[i][0].getTimeR()){
                SA_vector[i][0].setTimeP(SA_vector[i][0].getDishNo(), i);
                SA_vector[i][0].setTimeS(clock);
                SA_vector[i][0].setTimeC(SA_vector[i][0].getTimeS()+SA_vector[i][0].getTimeP());
                SA_vector[i][0].setTimeW(SA_vector[i][0].getTimeC()-SA_vector[i][0].getTimeR());
                timer[i]=SA_vector[i][0].getTimeC();
                totalWaiting += SA_vector[i][0].getTimeW();
                result.insert(result.end(), SA_vector[i][0]);
                SA_vector[i].erase(SA_vector[i].begin());
            }
        }
    for(int i=1; i<=machine; i++)
        if(!SA_vector[i].empty())
            return false;
    return true;
}

void SA::addOrder(Dishes newDish){
    order.insert(order.end(), newDish);
}

void SA::swap(int i1 , int j1, int i2, int j2){
    Dishes hold = SA_newVector[i1][j1];
    SA_newVector[i1][j1] = SA_newVector[i2][j2];
    SA_newVector[i2][j2] = hold;
}

void SA::resetOrder(){
    order.clear();
    for(int i=1; i<=machine; i++){
        for(int j=0; j<SA_vector[i].size(); j++)
            order.insert(order.end(), SA_vector[i][j]);
    }
}

void SA::resetSAVector(int clock){
    minProcess(clock);
    int j=0;
    if(!order.empty()){
        sort(order.begin(), order.end(), SA_order); 
        for(int i=1; i<=machine; i++){
            SA_vector[i].clear();
            while(j<order.size()){
                SA_vector[i].insert(SA_vector[i].end(), order[j++]);
                if(order[j].getMachineNo() != i)
                    break;
            }
        }
    }
}

void SA:: perturbation(int clock){
    vector<Dishes> temp;
    for(int i=1; i<=machine; i++)
        SA_newVector[i] = SA_vector[i];
    if (k<60){
        for(int b=0;b<10;b++){
            int i1=rand()%machine+1;
            int j1=rand()%SA_newVector[i1].size();
            int i2=rand()%machine+1;
            int j2=rand()%SA_newVector[i2].size();
            swap(i1, j1, i2, j2);
        }
        k++;
    }
    else{
        for(int b=0;b<3;b++){
            int i1=rand()%machine+1;
            int j1=rand()%SA_newVector[i1].size();
            int i2=rand()%machine+1;
            int j2=rand()%SA_newVector[i2].size();
            swap(i1, j1, i2, j2);}
            k=k+1;}
            updatingVector();
            countScheduleResult(clock);
}

void SA:: updatingVector(){
    SA_NewWaiting=0;

    for(int i=1;i<=machine;i++)
        for(int j=0;j<SA_newVector[i].size();j++)
            SA_NewWaiting+=SA_newVector[i][j].getTimeW();
}

void SA::acceptance()
{
    ofstream fout("result.txt");
    double delta = SA_totalWaiting-SA_NewWaiting;
    double alpha = exp(delta/T);
    srand( time(NULL));
    double random = ((double)(rand()%101))/100;
    if (SA_totalWaiting > SA_NewWaiting) //accept the better solution
    {
        for( int i=1;i<=machine;i++){
            for(int j=0;j<SA_vector[i].size();j++){
                SA_vector[i][j]=SA_newVector[i][j];}
            SA_totalWaiting=SA_NewWaiting;
            T=0.9*T;
        }
    }
    else if(alpha > random){    //accept the worse solution
        for( int i=1;i<=machine;i++){
            for(int j=0;j<SA_vector[i].size();j++){
                SA_vector[i][j]=SA_newVector[i][j];}
            SA_totalWaiting=SA_NewWaiting;
            T=0.98*T;
        }
    }
    fout<< T<<endl;
    for(int i=1;i<=machine;i++){
        for(int j=0;j<SA_vector[i].size();j++){
            fout << SA_vector[i][j].getNo() << ' ';}
        fout << endl;}
        loop++;
}

void SA::countScheduleResult(int clock){
    int *tempTimer = new int [machine+1];
    for(int i=1; i<=machine; i++)
        tempTimer[i] = timer[i];
    SA_NewWaiting = 0;

    for(int i=1; i<=machine; i++){
        for(int j=0; j<SA_newVector[i].size();){
            if(tempTimer[i] >= SA_newVector[i][j].getTimeR()){
                SA_newVector[i][j].setTimeP(SA_newVector[i][j].getDishNo(), i);
                SA_newVector[i][j].setTimeS(tempTimer[i]);
                tempTimer[i] += SA_newVector[i][j].getTimeP();
                SA_newVector[i][j].setTimeC(SA_newVector[i][j].getTimeS() + SA_newVector[i][j].getTimeP());
                SA_newVector[i][j].setTimeW(SA_newVector[i][j].getTimeC() - SA_newVector[i][j].getTimeR());
                SA_NewWaiting += SA_newVector[i][j].getTimeW();
                j++;
            }
            else
                tempTimer[i]++;
        }
    }
    delete [] tempTimer;
}

void SA::minProcess(int clock){
    int size = order.size();
    bool *dealed = new bool [num+1];
    memset(dealed, true, num+1);
    for(int i = 0; i<order.size(); i++)
        order[i].setMachineNo(0);
    int *minpTimer = new int [machine+1];
    for(int i=0; i<=machine; i++)
        minpTimer[i] = clock;
    vector<vector<Dishes>> machineTpOrder(machine+1);
    for(int i=1; i<=machine; i++){
        machineTpOrder[i].clear();
        machineTpOrder[i] = order;
        for(int j=0; j<order.size(); j++)
            machineTpOrder[i][j].setTimeP(machineTpOrder[i][j].getDishNo(), i);
        sort(machineTpOrder[i].begin(), machineTpOrder[i].end(), TpCmp);
    }

    int i(0);
    while(i<order.size()){
        for(int k=1; k<=machine && i<order.size(); k++){
            if(clock>=minpTimer[k]){
                bool deal(false);
                for(int j=0; j<order.size(); j++){
                    if(dealed[machineTpOrder[k][j].getNo()] && minpTimer[k] >= machineTpOrder[k][j].getTimeR()){
                        dealed[machineTpOrder[k][j].getNo()] = false;
                        machineTpOrder[k][j].setMachineNo(k);
                        machineTpOrder[k][j].setTimeS(clock);
                        machineTpOrder[k][j].setTimeC(machineTpOrder[k][j].getTimeS() + machineTpOrder[k][j].getTimeP());
                        machineTpOrder[k][j].setTimeW(machineTpOrder[k][j].getTimeC() - machineTpOrder[k][j].getTimeR());
                        minpTimer[k]+=machineTpOrder[k][j].getTimeP();
                        deal = true;
                        break;
                    }
                }
                if(deal){
                    i++;
                }
                else
                    minpTimer[k]++;
            }
        }
        clock++;
    }
    for(int i=1; i<=machine; i++)
        sort(machineTpOrder[i].begin(), machineTpOrder[i].end(), dishNoCmp);
    sort(order.begin(), order.end(), dishNoCmp);

    for(int i=0; i<order.size(); i++)
        for(int j=1; j<=machine; j++){
            if(machineTpOrder[j][i].getMachineNo() > 0 && machineTpOrder[j][i].getMachineNo() <= machine){
                order[i] = machineTpOrder[j][i];
                //break;
            }
        }
    delete[] dealed;
    delete[] minpTimer;
}

void SA::printResult(){
    int a=0;
    cout<<"Using SA\n";
    Algorithm::getResult(result);
}
