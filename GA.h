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
#include "Algorithm.h"

using namespace std;

class GA : public Algorithm{
    public:
        GA(vector<Dishes>, vector<Dishes>, int, int);
        ~GA();
        static bool initSort(Dishes, Dishes);
        vector<Dishes> setOrder();
        void printResult();
    private:
        void init();
        void crossOver();
        void mutation();
        vector<Dishes> p1, p2;
};

#endif
