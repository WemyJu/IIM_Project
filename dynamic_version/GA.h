//
// IIM project
// GA.h
// Created by Wemy Ju on 28/08/2015.
//

#ifndef GA_H
#define GA_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <ctime>
#include "Algorithm.h"

using namespace std;

class GA : public Algorithm{
    public:
        GA(int, int);
        ~GA();
        static bool initSort(Dishes, Dishes);
        static bool resultSort(Dishes, Dishes);
        static bool firstComeCmp(Dishes, Dishes);
        static bool dishNoCmp(Dishes, Dishes);
        static bool TpCmp(Dishes, Dishes);
        void addOrder(int, Dishes);
        bool checkSchedule(int);
        vector<Dishes> setOrder();
        void printResult();
    private:
        void init();
        void crossOver();
        void mutation();
        void swap(int, int);
        vector<Dishes> fifo(int, vector<Dishes>);
        vector<Dishes> minProcess(int, vector<Dishes>);
        int machine, number;
        vector<Dishes> p1, p2;
        int *gaTimer;
};

#endif
