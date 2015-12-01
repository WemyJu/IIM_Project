//
// IIM project
// Machine.h
// Created by Wemy Ju on 19/08/2015.
//

#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <fstream>
#include <string>
#include "Dishes.h"

using namespace std;

class Machine{
    public:
        static void setMachine(int&, int&);
        static void printProcessing();
    private:
        int static machineNum, dishNum;
        int static **tempTp;
};

#endif
