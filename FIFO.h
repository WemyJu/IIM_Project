// 
// IIM project
// FIFO.h
// Created by Wemy Ju on 16/07/2015.
//

#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include "Algorithm.h"

using namespace std;

class FIFO : public Algorithm{
    public:
        FIFO(vector<Dishes*>, int, int);
        ~FIFO();
        static bool firstComeCmp(Dishes*, Dishes*);
        void setOrder();
        void printResult();
    private:
        int clock, machine;
        int *timer;
};

#endif
