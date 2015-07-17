//
// IIM project
// Algorithm.cpp
// Created bt Wemy Ju on 16/07/2015.
//

#include "Algorithm.h"

Algorithm::Algorithm(int num){
//void Algorithm::initOrders(vector<Dishes*> orders, int num){
//void Algorithm::initOrders(int){
    srand(time(NULL));
    
    for(int i=0; i<num; i++){
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
        orders.push_back(dish);
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
        cout << " " << setw(5) << order[i]->getNo()
        << setw(9) << order[i]->getTimeR()
        << setw(7) << order[i]->getTimeS()
        << setw(9) << order[i]->getTimeP()
        << setw(10) << order[i]->getTimeC()
        << setw(9) << order[i]->getTimeW() << endl;
    cout << "Total Waiting Time : " << totalWaiting << endl;
    cout << "Complete Time : " << completeTime << endl;
    cout << endl << endl;
}
