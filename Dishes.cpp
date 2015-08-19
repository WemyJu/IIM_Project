//
// IIM project
// Dishes.cpp
// Created by Wemy Jy on 09/07/2015.
//

#include "Dishes.h"

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

void Dishes::setTimeP(int p){
    process = p;
}

void Dishes::setTable(int t){
    table = t;
}

void Dishes::setName(string n){
    name = n;
}
