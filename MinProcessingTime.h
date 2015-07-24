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
        MinProcessingTime(vector<Dishes*>, int);
        ~MinProcessingTime();
        static bool TpCmp(Dishes*, Dishes*);
        static bool TsCmp(Dishes*, Dishes*);
        void setOrder();
        void printResult();
    private:
        int timer;
};

#endif
