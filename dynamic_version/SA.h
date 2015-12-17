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
		SA(vector<Dishes> , int , int );
		bool static SA_order(Dishes ,Dishes );
        bool static TrCmp(Dishes, Dishes);
		void compareTW(int& , int&);
        bool checkSchedule(int);
        void addOrder(Dishes);
		void logic(int ,int );
		void perturbation();
		void updatingVector();
		void acceptance();
		void printResult();
	private:
		void swap(int ,int ,int ,int );
        void countScheduleResult();
		int clock, machine;
		int SA_totalWaiting;
		int MA_totalWaiting;
		vector<vector<Dishes> > SA_vector;
	    vector<vector<Dishes> > SA_newVector;
	    int SA_NewWaiting, k, T, loop;
        int *timer;
};
#endif
