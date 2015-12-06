//
// IIM project
// Dishes.cpp
// Created by Wemy Jy on 09/07/2015.
//

#include "Dishes.h"

int Dishes::machine = 0;
int Dishes::dish = 0;
int** Dishes::Tp = NULL;
string* Dishes::dishName = NULL;

// get functions
void Dishes::deleteDynamicArray(){
    for(int i=0; i<machine; i++)
        delete [] Tp[i];
    delete [] Tp;

    delete [] dishName;
}

int Dishes::getMachine(){
    return machine;
}

int Dishes::getDish(){
    return dish;
}

string Dishes::getDishName(int index){
    return dishName[index];
}

int Dishes::getDishIndex(string name){
    for(int i=1; i<=dish; i++)
        if(strcmp(dishName[i].c_str(), name.c_str()) == 0)
            return i;
    return 0;
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


int Dishes::getDishNo(){
    return dishNo;
}

int Dishes::getMachineNo(){
    return machineNo;
}

string Dishes::getName(){
    return name;
}

// set finctions 
void Dishes::setMachine(int m){
    machine = m;
}

void Dishes::setDish(int d){
    dish = d;
}

void Dishes::setProcessingTime(int **Tps){
    Tp = Tps;
}

void Dishes::setDishName(string* names){
    dishName = names;
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

void Dishes::setNo(int NO){
    No = NO;
}

void Dishes::setTable(int t){
    table = t;
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
