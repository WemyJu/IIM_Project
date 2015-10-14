//
// IIM project
// MinProcessingTime.h
// Created by Wemy Ju on 21/07/2015.
//

#ifndef MINPROCESSINGTIME_H
#define MINPROCESSINGTIME_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include "Algorithm.h"

using namespace std;

class MinProcessingTime : Algorithm{
    public:
        MinProcessingTime(int, int);
        ~MinProcessingTime();
        static bool TpCmp(Dishes, Dishes);
        static bool TsCmp(Dishes, Dishes);
        static bool DishNoCmp(Dishes, Dishes);
        void addOrder(int, Dishes);
        bool checkSchedule(int);
        void printResult();
    private:
        vector<vector<Dishes>> machineTpOrder;
        int machine, clock;
        int *timer;
        bool *dealed;
};

#endif
