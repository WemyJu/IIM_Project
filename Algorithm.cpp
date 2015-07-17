//
// IIM project
// Algorithm.cpp
// Created bt Wemy Ju on 16/07/2015.
//

#include "Algorithm.h"

void Algorithm::initOrder(vector<Dishes*>& ordering, int& n){
    srand(time(NULL));
    n = rand()%10+10;
    for(int i=0; i<n; i++){
        Dishes *dish;
        switch(rand()%3+1){
            case 1:
                dish = new Dish1;
                break;
            case 2:
                dish = new Dish2;
                break;
            case 3:
                dish = new Dish3;
                break;
        }
        dish->setNo(i);
        dish->setTimeR(0);
        dish->setTimeP();
        dish->setName();
        ordering.push_back(dish);
    }
}

int Algorithm::getTotalWaiting(){
    return totalWaiting;
}

int Algorithm::getCompleteTime(){
    return completeTime;
}

void Algorithm::getResult(vector<Dishes*> order){
    cout << "-------------------------------------------------\n";
    cout << " No.  Release  Start  Process  Complete  Waiting \n";
    for(int i=0; i<num; i++)
        cout << " " << setw(2) << order[i]->getNo()
        << setw(10) << order[i]->getTimeR()
        << setw(7) << order[i]->getTimeS()
        << setw(9) << order[i]->getTimeP()
        << setw(10) << order[i]->getTimeC()
        << setw(9) << order[i]->getTimeW() << endl;
    cout << "Total Waiting Time : " << totalWaiting << endl;
    cout << "Complete Time : " << completeTime << endl;
    cout << endl << endl;
}
