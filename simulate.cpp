//
// IIM project
// simulate.cpp
// Created by Wemy Ju on 16/07/2015.
//

#include <iostream>
#include "Dishes.h"
#include "Dish1.h"
#include "Dish2.h"
#include "Dish3.h"
#include "Algorithm.h"
#include "FIFO.h"
#include "MinProcessingTime.h"

using namespace std;

int main(){
    vector<Dishes*> order;
    int numOfOrder(0);

    Algorithm::initOrder(order, numOfOrder);
    FIFO fifo(order, numOfOrder);
    fifo.setOrder();
    fifo.printResult();
    MinProcessingTime minTp(order, numOfOrder);
    minTp.setOrder();
    minTp.printResult();
}
