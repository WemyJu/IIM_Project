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
        string getName();
    protected:
        void setNo(int);
        void setTimeR(int);
        void setTimeS(int);
        void setTimeC(int);
        void setTimeW(int);
        virtual void setName() = 0;
        virtual void setTimeP() = 0;
        int process, start, release, complete, No, waiting;
        string name;
};

#endif
