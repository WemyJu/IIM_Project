//
// IIM project
// Algorithm.cpp
// Created bt Wemy Ju on 16/07/2015.
//

#include "Algorithm.h"

string* Algorithm::dishName = NULL;

void Algorithm::initOrder(vector<Dishes>& ordering, int& n, int& d){
    int nextTime(0), order_num(0);
    srand(time(NULL));
    n = rand()%10+50;
    dishName = new string [d+1];

    getDishName();

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
            dish.setDishNo(dishNum);
            dish.setName(dishName[dishNum]);
            dish.setTimeR(Tr);
            //dish.setTimeR(0);
            dish.setNo(i+1);
            dish.setTable(table);
            ordering.push_back(dish);
        }
        if(i>n)
            n=i;
    }

    delete [] dishName;
}

int Algorithm::getTotalWaiting(){
    return totalWaiting;
}

int Algorithm::getCompleteTime(){
    return completeTime;
}

void Algorithm::getResult(vector<Dishes> result){
    cout << "-----------------------------------------------------------------\n";
    cout << " No.  Table  Release  Machine  Start  Process  Complete  Waiting \n";
    for(int i=0; i<num; i++)
        cout << " " << setw(3) << result[i].getNo()
             << setw(7) << result[i].getTable()
             << setw(9) << result[i].getTimeR()
             << setw(9) << result[i].getMachineNo()
             << setw(7) << result[i].getTimeS()
             << setw(9) << result[i].getTimeP()
             << setw(10) << result[i].getTimeC()
             << setw(9) << result[i].getTimeW() << endl;
    cout << "Total Waiting Time : " << totalWaiting << endl;
    cout << "Complete Time : " << completeTime << endl;
    cout << endl << endl;
}

void Algorithm::getDishName(){
    fstream fp;
    int machineNum, dishNum;

    fp.open("FireMeat.txt", ios::in);
    fp >> machineNum >> dishNum;
    for(int i=1; i<=dishNum; i++)
        fp >> dishName[i];
    fp.close();
}
