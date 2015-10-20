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

    fp.open("ProcessingTime.txt", ios::in);
    fp >> machineNum >> dishNum;
    Tps = new int*[machineNum];
    for(int i=0; i<machineNum; i++){
        Tps[i] = new int[dishNum];
        for(int j=0; j<dishNum; j++)
            fp >> Tps[i][j];
    }

    machine = machineNum;
    dish = dishNum;
    Dishes::setMachine(machineNum);
    Dishes::setProcessingTime(Tps);
    tempTp = Tps;
}

void Machine::printProcessing(){
    cout << "in machine, num = "<< machineNum << " " << dishNum << "\n";
    for(int i=0; i<3 ;i++){
        for(int j=0; j<3; j++)
            cout << tempTp[i][j] << " ";
        cout << endl;
    }
}

int **Machine::tempTp = NULL;

