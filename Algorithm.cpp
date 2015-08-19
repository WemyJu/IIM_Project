//
// IIM project
// Algorithm.cpp
// Created bt Wemy Ju on 16/07/2015.
//

#include "Algorithm.h"

void Algorithm::initOrder(vector<Dishes*>& ordering, int& n){
    int nextTime(0), order_num(0);
    srand(time(NULL));
    n = rand()%10+30;

    default_random_engine generator(time(NULL));
    poisson_distribution<int> possion_dis(5);
    normal_distribution<double> normal_dis(3, 1);

    int Tr(0), table(1);
    for(int i=0; i<n; table++){
        do
            order_num = (int)normal_dis(generator);
        while(order_num <= 0);
        Tr += possion_dis(generator);
        for(int j=0; j<order_num; j++, i++){
            Dishes *dish = new Dishes;
            switch(rand()%3+1){
                case 1:
                    dish->setName("Dish No.1");
                    dish->setTimeP(7);
                    break;
                case 2:
                    dish->setName("Dish No.2");
                    dish->setTimeP(9);
                    break;
                case 3:
                    dish->setName("Dish No.3");
                    dish->setTimeP(11);
                    break;
            }
            dish->setTimeR(Tr);
            dish->setNo(i+1);
            dish->setTable(table);
            ordering.push_back(dish);
        }
        if(i>n)
            n=i;
    }
}

int Algorithm::getTotalWaiting(){
    return totalWaiting;
}

int Algorithm::getCompleteTime(){
    return completeTime;
}

void Algorithm::getResult(vector<Dishes*> order){
    cout << "-------------------------------------------------\n";
    cout << " No.  Table  Release  Start  Process  Complete  Waiting \n";
    for(int i=0; i<num; i++)
        cout << " " << setw(3) << order[i]->getNo()
            << setw(7) << order[i]->getTable()
            << setw(9) << order[i]->getTimeR()
            << setw(7) << order[i]->getTimeS()
            << setw(9) << order[i]->getTimeP()
            << setw(10) << order[i]->getTimeC()
            << setw(9) << order[i]->getTimeW() << endl;
    cout << "Total Waiting Time : " << totalWaiting << endl;
    cout << "Complete Time : " << completeTime << endl;
    cout << endl << endl;
}
