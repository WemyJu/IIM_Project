// 
// IIM project
// FIFO.h
// Created by Wemy Ju on 16/07/2015.
//

#ifndef FIFO_H
#define FIFO_H

#include <iostream>
//#include <vector>
#include <algorithm>
#include "Algorithm.h"
//#include "Dishes.h"

using namespace std;

class FIFO : public Algorithm{
    public:
        FIFO();
        ~FIFO();
        static bool firstComeCmp(Dishes*, Dishes*);
        void setOrder();
        void printResult();
    private:
        vector<Dishes*> order;
        //int num;
        int timer;
};

#endif
