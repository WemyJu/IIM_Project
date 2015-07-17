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
#include "Dishes.h"
#include "Dish1.h"
#include "Dish2.h"
#include "Dish3.h"

class Algorithm{
    public:
        Algorithm(int);
        Algorithm(){};
        //virtual ~Algorithm() = 0;
        //static void initOrders(vector<Dishes*>, int);
        int getTotalWaiting();
        int getCompleteTime();
        void getResult(vector<Dishes*>);
    protected:
        virtual void getAlgorithmName(){};
        int totalWaiting, completeTime, num;
        vector<Dishes*> orders;
};

#endif
