//
// IIM project
// simulate.cpp
// Created by Wemy Ju on 16/07/2015.
//

#include <iostream>
//#include <vector>
//#include <ctime>
//#include <cstdlib>
//#include <iomanip>
//#include "initOrder.h"
#include "Dishes.h"
#include "Dish1.h"
#include "Dish2.h"
#include "Dish3.h"
#include "Algorithm.h"
#include "FIFO.h"

using namespace std;

//void initOrders(vector<Order>, int);

int main(){
    ///vector<Dishes*> order(20);
    Algorithm oriOrder(20);
    //Algorithm::initOrders(order, 20);
    //Algorithm *a;
    //(*a).initOrders(order, 20);
    FIFO fifo;
    //fifo.setOrder();
    //fifo.getAlgorithmName();
    //fifo.printResult();
}

/*void initOrders(vector<Order> order, int num){
    srand(time(NULL));
    
    for(int i=0; i<num; i++){
        order[i]->setNo(i);
        order[i]->setTimeR(0);
        switch(rand()%3+1){
            case 1:
                order[i] = new Dish1;
                break;
            case 2:
                order[i] = new Dish2;
                break;
            case 3:
                order[i] = new Dish3;
                break;
        }
        order[i]->setTimeP();
        order[i]->setName();
    }
}*/

