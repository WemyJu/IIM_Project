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
#include <cstring>
#include <sstream>
#include <iomanip>
#include <random>
#include <string>
#include <fstream>
#include "Dishes.h"

class Algorithm{
    public:
        Algorithm(){};
        //~Algorithm();
        static void initOrder(vector<Dishes>&, int&, int, int, char* []);
        int getTotalWaiting();
        int getCompleteTime();
        void getResult(vector<Dishes>);
        vector<Dishes> getScheduleResult();
    protected:
        int totalWaiting, completeTime; 
        int num;
        vector<Dishes> order;
        vector<Dishes> result;
    private:
        static vector<Dishes> produceOrders(int&, int);
        static vector<Dishes> readOrders(int&, int, char* []);
        static string *dishName;
};

#endif
