//
// IIM project
// Algorithm.h
// Created by Wemy Ju on 16/07/2015.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <random>
#include "Dishes.h"
#include "Dish1.h"
#include "Dish2.h"
#include "Dish3.h"

class Algorithm{
    public:
        Algorithm(){};
        static void initOrder(vector<Dishes*>&, int&);
        int getTotalWaiting();
        int getCompleteTime();
        void getResult(vector<Dishes*>);
    protected:
        int totalWaiting, completeTime, num;
        vector<Dishes*> order;
};

#endif
