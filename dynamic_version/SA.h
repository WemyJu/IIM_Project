#ifndef SA_H
#define SA_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include "Algorithm.h"

using namespace std;

class SA : public Algorithm
{
	public:
		SA(int , int );
		bool static SA_order(Dishes ,Dishes );
        bool static TrCmp(Dishes, Dishes);
        bool static dishNoCmp(Dishes, Dishes);
        bool static TpCmp(Dishes, Dishes);
		void compareTW(int& , int&);
        bool checkSchedule(int);
        void addOrder(Dishes);
        void resetOrder();
        void resetSAVector(int);
		void logic(int);
		void updatingVector();
		void acceptance();
		void printResult();
	private:
		void swap(int ,int ,int ,int);
		void perturbation(int);
        void countScheduleResult(int);
        void minProcess(int);
		int machine;
		int SA_totalWaiting;
		int MA_totalWaiting;
		vector<vector<Dishes> > SA_vector;
	    vector<vector<Dishes> > SA_newVector;
	    int SA_NewWaiting, k, T, loop;
        int *timer;
};
#endif
