//
// IIM project
// Dishes.cpp
// Created by Wemy Jy on 09/07/2015.
//

#include "Dishes.h"

int Dishes::machine = 0;
int** Dishes::Tp = NULL;

void Dishes::setProcessingTime(int **Tps){
    Tp = Tps;
}

void Dishes::deleteTp(){
    for(int i=0; i<machine; i++)
        delete [] Tp[i];
    delete Tp;
}

int Dishes::getTimeS(){
    return start;
}

int Dishes::getTimeP(){
    return process;
}

int Dishes::getTimeC(){
    return complete;
}

int Dishes::getTimeR(){
    return release;
}

int Dishes::getTimeW(){
    return waiting;
}

int Dishes::getNo(){
    return No;
}

int Dishes::getTable(){
    return table;
}

int Dishes::getMachine(){
    return machine;
}

int Dishes::getDishNo(){
    return dishNo;
}

int Dishes::getMachineNo(){
    return machineNo;
}

string Dishes::getName(){
    return name;
}

void Dishes::setNo(int NO){
    No = NO;
}

void Dishes::setTimeR(int r){
    release = r;
}

void Dishes::setTimeS(int s){
    start = s;
}

void Dishes::setTimeC(int c){
    complete = c;
}

void Dishes::setTimeW(int w){
    waiting = w;
}

void Dishes::setTimeP(int dish, int machine){
    process = Tp[machine-1][dish-1];
}

void Dishes::setTable(int t){
    table = t;
}

void Dishes::setMachine(int m){
    machine = m;
}

void Dishes::setDishNo(int no){
    dishNo = no;
}

void Dishes::setMachineNo(int no){
    machineNo = no;
}

void Dishes::setName(string n){
    name = n;
}
