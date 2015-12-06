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
        friend class Machine;
        friend class Algorithm;
        friend class FIFO;
        friend class MinProcessingTime;
        friend class GA;
        friend class SA;
        // ~Dishes();
        static void deleteDynamicArray();
        static int getMachine();  // get total number of machine
        static int getDish();  //get total number of dish
        static string getDishName(int);  // find the dish name by No.
        static int getDishIndex(string);  // find the dish No. by name
        int getTimeS();  // get start time
        int getTimeP();  // get processing time
        int getTimeC();  // get complete time
        int getTimeR();  // get release time
        int getTimeW();  // get waiting time
        int getNo();  // get dishes NO.
        int getTable();  // get table No.
        int getDishNo();  // get dish No.
        int getMachineNo();  // get machine No.
        string getName();  // get dish name
    protected:
        static void setMachine(int);
        static void setDish(int);
        static void setProcessingTime(int**);
        static void setDishName(string*);
        void setTimeR(int);
        void setTimeS(int);
        void setTimeC(int);
        void setTimeW(int);
        void setTimeP(int, int);
        void setNo(int);
        void setTable(int);
        void setDishNo(int);
        void setMachineNo(int);
        void setName(string);
        int process, start, release, complete, No, waiting, table, dishNo, machineNo;
        string name;
        static int machine, dish;
        static int **Tp;
        static string *dishName;
};

#endif
