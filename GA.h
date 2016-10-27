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
#include <queue>
#include <unistd.h>
#include "Algorithm.h"

using namespace std;

class GA : public Algorithm{
    public:
        typedef struct{
            int index;
            int Tw;
        }CHILDINFO;

        typedef struct{
             bool operator() (const CHILDINFO& a, const CHILDINFO& b){
                 return a.Tw > b.Tw;
             }
        }chooseGenerations;

        GA(int, int);
        GA();
        ~GA();
        static bool initSort(Dishes, Dishes);
        static bool resultSort(Dishes, Dishes);
        static bool firstComeCmp(Dishes, Dishes);
        static bool dishNoCmp(Dishes, Dishes);
        static bool TpCmp(Dishes, Dishes);
        static bool machineCmp(Dishes, Dishes);
        void operator=(GA ga);
        void addOrder(Dishes);
        void findBest(int);
        void findBetter(int);
        void generateChild(int);
        bool checkSchedule(int);
        void printResult();
    private:
        void crossOver();
        void mutation();
        void swap(int, int, int);
        vector<Dishes> fifo(int, vector<Dishes>);
        vector<Dishes> minProcess(int, vector<Dishes>);
        int machine;
        vector<Dishes> p[40];
        vector<Dishes> c[1250];
        int *gaTimer;
        int childNum;
        const int MAXINT = 2147483647;
};

#endif
