//
// IIM project
// Algorithm.cpp
// Created bt Wemy Ju on 16/07/2015.
//

#include "Algorithm.h"

void Algorithm::initOrder(vector<Dishes>& ordering, int& n, int& d){
    int nextTime(0), order_num(0);
    srand(time(NULL));
    n = rand()%10+50;

    default_random_engine generator(time(NULL));
    poisson_distribution<int> possion_dis(5);
    normal_distribution<double> normal_dis(6, 2);
    normal_distribution<double> normal_dis2(60, 30);

    int Tr(0), table(1);
    Dishes dish;
    for(int i=0; i<n; table++){
        do 
            order_num = (int)normal_dis(generator);
        while(order_num <= 0);
        //Tr += possion_dis(generator);
        do 
            Tr = normal_dis2(generator);
        while(Tr<0);

        for(int j=0; j<order_num; j++, i++){
            //Dishes *dish = new Dishes;
            int dishNum = rand()%d+1;
            char a='0'+dishNum;
            string name = "Dish No.";
            name += a;
            dish.setName(name);
            dish.setDishNo(dishNum);
            dish.setTimeR(Tr);
            //dish.setTimeR(0);
            dish.setNo(i+1);
            dish.setTable(table);
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

void Algorithm::getResult(vector<Dishes> order){
    cout << "-----------------------------------------------------------------\n";
    cout << " No.  Table  Release  Machine  Start  Process  Complete  Waiting \n";
    for(int i=0; i<num; i++)
        cout << " " << setw(3) << order[i].getNo()
             << setw(7) << order[i].getTable()
             << setw(9) << order[i].getTimeR()
             << setw(9) << order[i].getMachineNo()
             << setw(7) << order[i].getTimeS()
             << setw(9) << order[i].getTimeP()
             << setw(10) << order[i].getTimeC()
             << setw(9) << order[i].getTimeW() << endl;
    cout << "Total Waiting Time : " << totalWaiting << endl;
    cout << "Complete Time : " << completeTime << endl;
    cout << endl << endl;
}
