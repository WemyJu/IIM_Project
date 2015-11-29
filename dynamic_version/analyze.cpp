//
// IIM project
// analyze.cpp
// Created by Wemy Ju on 09/11/2015.
//

#include <iostream>
#include <iomanip>
#include "Dishes.h"
#include "Machine.h"
#include "Algorithm.h"
#include "FIFO.h"
#include "MinProcessingTime.h"
#include "GA.h"

using namespace std;

bool timeRCmp(Dishes a, Dishes b){
    return a.getTimeR() < b.getTimeR();
}

int main(){
    double fifoTwPerDish(0), fifoTcPerDish(0), minProTwPerDish(0), minProTcPerDish(0), gaTwPerDish(0), gaTcPerDish(0);
    int const times(10);

    for(int i; i<times; i++){
        vector<Dishes> order, oriOrder;
        int numOfOrder(0), machine(0), clock(0), numOfDish(0);
        bool fifoEnd(false), minProEnd(false), GAEnd(false); 

        Machine::setMachine(machine, numOfDish);
        //Machine::printProcessing();
        Algorithm::initOrder(order, numOfOrder, numOfDish);
        sort(order.begin(), order.end(), timeRCmp);
        oriOrder = order;

        FIFO fifo(machine, numOfOrder);
        MinProcessingTime minPro(machine, numOfOrder);
        while(!fifoEnd || !minProEnd || !order.empty()){
            while(clock >= order.begin()->getTimeR() && !order.empty()){
                Dishes dish = *(order.begin());
                fifo.addOrder(clock, dish);
                minPro.addOrder(clock, dish);
                order.erase(order.begin());
            }
            fifoEnd = fifo.checkSchedule(clock);
            minProEnd = minPro.checkSchedule(clock);
            clock++;
        }
        fifoTwPerDish += fifo.getTotalWaiting()/numOfOrder;
        fifoTcPerDish += fifo.getCompleteTime()/numOfOrder;
        minProTwPerDish += minPro.getTotalWaiting()/numOfOrder;
        minProTcPerDish += minPro.getCompleteTime()/numOfOrder;


        GA gaMinTw, gaMinTc, ga(machine, numOfOrder);
        order = oriOrder;
        clock = 0;
        bool addDish = false;
        while(!GAEnd || !order.empty()){
            while(clock >= order.begin()->getTimeR() && !order.empty()){
                Dishes dish = *(order.begin());
                ga.addOrder(dish);
                order.erase(order.begin());
                addDish = true;
            }
            if(addDish){
                ga.generateChild(clock);
                ga.findBest(clock);
                addDish = false;
            }
            GAEnd = ga.checkSchedule(clock);
            clock++;
        }

        gaTwPerDish += ga.getTotalWaiting()/numOfOrder;
        gaTcPerDish += ga.getCompleteTime()/numOfOrder;

        Dishes::deleteTp();
    }

    cout << "                       FIFO       Min Processing       GA\n"
         << "                     ============================================\n"
         << "Total Waiting Time     " << left << setw(11) << fifoTwPerDish/times << setw(21) << minProTwPerDish/times << setw(9) << gaTwPerDish/times << endl
         << "Total Complete Time    " << setw(11) << fifoTcPerDish/times << setw(21) << minProTcPerDish/times << setw(9) << gaTcPerDish/times << endl;
}
