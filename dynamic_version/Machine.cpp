//
// IIM project
// Machine.cpp
// Created by Wemy Ju on 19/08/2015.
//

#include "Machine.h"

int Machine::machineNum = 0;
int Machine::dishNum = 0;

void Machine::setMachine(int &machine, int &dish){
    fstream fp;
    int Tp;
    int **Tps;
    string* names;

    //fp.open("ProcessingTime.txt", ios::in);
    fp.open("FireMeal.txt", ios::in);
    //fp.open("test.txt", ios::in);
    fp >> machineNum >> dishNum;

    names = new string [dishNum+1];
    for(int i=1; i<=dishNum; i++){
        fp >> names[i];
    }
    
    Tps = new int*[machineNum];
    for(int i=0; i<machineNum; i++){
        Tps[i] = new int[dishNum];
        for(int j=0; j<dishNum; j++)
            fp >> Tps[i][j];
    }

    fp.close();
    machine = machineNum;
    dish = dishNum;

    Dishes::setMachine(machineNum);
    Dishes::setDish(dishNum);
    Dishes::setProcessingTime(Tps);
    Dishes::setDishName(names);
}
