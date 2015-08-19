//
// IIM project
// Dishes.h
// Created by Wemy Ju on 09/07/2015.
//

#ifndef DISHES_H
#define DISHES_H

#include <iostream>
#include <string>

using namespace std;

class Dishes{
    public:
        //friend void initilize(vector<Order>, int);
        friend class Algorithm;
        friend class FIFO;
        friend class MinProcessingTime;
        //virtual ~Dishes() = 0;
        int getTimeS();  // get start time
        int getTimeP();  // get processing time
        int getTimeC();  // get complete time
        int getTimeR();  // get release time
        int getTimeW();  // get waiting time
        int getNo();  // get NO.
        int getTable();  // get table
        string getName();  // get dish name
    protected:
        void setTimeR(int);
        void setTimeS(int);
        void setTimeC(int);
        void setTimeW(int);
        void setTimeP(int);
        void setNo(int);
        void setTable(int);
        void setName(string);
        int process, start, release, complete, No, waiting, table;
        string name;
};

#endif
