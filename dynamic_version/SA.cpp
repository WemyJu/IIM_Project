#include "SA.h"
#include <fstream>
using namespace std;


SA::SA(vector<Dishes> SA_dishes,int n,int m){
    order=SA_dishes;
    num = n;
    machine = m;
    k = 1;
    T=9999;
    loop=0;
    SA_totalWaiting=0;
    MA_totalWaiting=0;//machine total waiting time
    sort(order.begin(),order.end(),SA::SA_order);
    vector<Dishes> temp;
    for(int i=0;i<machine;i++){
        SA_vector.push_back(temp);
    } 
    for(int i =0;i<num;i++){
        SA_vector[order[i].getMachineNo()-1].push_back(order[i]);
    }
    for(int i=0;i<machine;i++){
        for(int j=0;j<SA_vector[i].size();j++){
            SA_totalWaiting += SA_vector[i][j].getTimeW();
            /*compareTW (SA_totalWaiting , MA_totalWaiting);**/}//choose max MA_totalWaiting to record in SA_totalWaiting	   
    }

    cout<<SA_totalWaiting<<endl;
    /*cout<<"machine 1"<<endl;
      for(int i=0;i<SA_vector[0].size();i++){
      cout<<"i="<< i <<SA_vector[0][i].getNo()<<endl;}
      cout<<"machine 2"<<endl;
      for(int i=0;i<SA_vector[1].size();i++){
      cout<<"i="<< i <<SA_vector[1][i].getNo()<<endl;}
      cout<<"machine 3"<<endl;
      for(int i=0;i<SA_vector[2].size();i++){
      cout<<"i="<< i <<SA_vector[2][i].getNo()<<endl;}*/


}

void SA::logic( int num , int machine)
{
    while(loop <= 10){
        perturbation();
        acceptance();}
}

void SA::compareTW (int &SAT, int &MAT)
{
    if( MAT > SAT)
    {
        SAT = MAT;
    }
}

bool SA::SA_order(Dishes a,Dishes b){
    if(a.getMachineNo()!=b.getMachineNo()){
        return a.getMachineNo() < b.getMachineNo();
    }
    else{
        return a.getTimeR() < b.getTimeR();
    }	
}

bool SA::TrCmp(Dishes a, Dishes b){
    if(a.getTimeR() != b.getTimeR())
        return a.getTimeR() < b.getTimeR();
    else
        return a.getTimeP() < b.getTimeP();
}

void SA:: perturbation(){
    vector<Dishes> temp;
    if(SA_newVector.size()!=0)
        SA_newVector.clear();
    for(int i=0;i<machine;i++){
        SA_newVector.push_back(temp);
    } 
    for(int i =0;i<num;i++){
        SA_newVector[order[i].getMachineNo()-1].push_back(order[i]);}
    if (k<60){
        for(int b=0;b<10;b++){
            int i1=rand()%machine;
            int j1=rand()%SA_newVector[i1].size();
            int i2=rand()%machine;
            int j2=rand()%SA_newVector[i2].size();
            swap(i1, j1, i2, j2);
        } 
        k=k+1;  
    }
    else{
        for(int b=0;b<3;b++){
            int i1=rand()%machine;
            int j1=rand()%SA_newVector[i1].size();
            int i2=rand()%machine+1;
            int j2=rand()%SA_newVector[i2].size();
            swap(i1, j1, i2, j2);}
            k=k+1;}
            updatingVector();
            countScheduleResult();
            cout<<"after swap"<<SA_NewWaiting<<endl;
}

void SA::swap(int i1 , int j1, int i2, int j2){
    Dishes hold = SA_newVector[i1][j1];
    SA_newVector[i1][j1] = SA_newVector[i2][j2];
    SA_newVector[i2][j2] = hold;}

    void SA:: updatingVector(){
        SA_NewWaiting=0;
        cout<<"updating vector"<<SA_NewWaiting;


        for(int i=0;i<machine;i++){
            for(int j=0;j<SA_newVector[i].size();j++){
                SA_NewWaiting+=SA_newVector[i][j].getTimeW();
                //cout << "new waiting = " << SA_NewWaiting << " Tw = " << SA_newVector[i][j].getTimeW() << endl;
            }
            /*compareTW(SA_NewWaiting , MA_totalWaiting);*///choose max MA_totalWaiting to record in SA_totalWaiting	   
        }
    }

void SA::acceptance() 
{   
    ofstream fout("result.txt");
    double delta = SA_totalWaiting-SA_NewWaiting;
    double alpha = exp(delta/T);
    cout<<"delta="<<delta<<endl;
    cout<<"alpha="<<alpha<<endl;
    srand( time(NULL));
    double random = ((double)(rand()%101))/100;
    cout<<"random="<<random<<endl;
    cout<<"SA_totalwaiting="<<SA_totalWaiting<<endl;
    cout<<"SA_NewWaiting="<<SA_NewWaiting<<endl;
    if (SA_totalWaiting > SA_NewWaiting) //accept the better solution
    {
        for( int i=0;i<machine;i++){
            for(int j=0;j<SA_vector[i].size();j++){
                SA_vector[i][j]=SA_newVector[i][j];}
            SA_totalWaiting=SA_NewWaiting;
            T=0.9*T;
        }

        cout<<"1"<<endl;
    }
    else if( alpha > random){    //accept the worse solution
        for( int i=0;i<machine;i++){
            for(int j=0;j<SA_vector[i].size();j++){
                SA_vector[i][j]=SA_newVector[i][j];}
            SA_totalWaiting=SA_NewWaiting;
            T=0.98*T;
        } 
        cout<<"2"<<endl;
    }
    cout<<"after acceptance"<<endl;
    fout<< T<<endl;
    for(int i=0;i<machine;i++){
        for(int j=0;j<SA_vector[i].size();j++){
            fout << SA_vector[i][j].getNo() << ' ';}
        fout << endl;}
        loop=loop+1;
        cout<<"loop="<<loop<<endl;
        cout<<"T="<<T<<endl;
}

void SA::countScheduleResult(){
    int timer(0);
    clock = 0;
    SA_NewWaiting = 0;

    for(int i=0; i<machine; i++)
        sort(SA_newVector[i].begin(), SA_newVector[i].end(), TrCmp);
    for(int i=0; i<machine; i++){
        timer = 0;
        for(int j=0; j<SA_newVector[i].size();){
            if(timer >= SA_newVector[i][j].getTimeR()){
                SA_newVector[i][j].setTimeP(SA_newVector[i][j].getDishNo(), i+1);
                SA_newVector[i][j].setTimeS(timer);
                timer += SA_newVector[i][j].getTimeP();
                SA_newVector[i][j].setTimeC(timer);
                SA_newVector[i][j].setTimeW(timer - SA_newVector[i][j].getTimeR());
                SA_NewWaiting += SA_newVector[i][j].getTimeW();
                j++;
            }
            else
                timer++;
        }
    }

}

void SA::printResult(){
    int a=0;
    cout<<"Using SA\n";
    cout << "-----------------------------------------------------------------\n";
    cout << " No.  Table  Release  Machine  Start  Process  Complete  Waiting \n";
    for( int i=0;i<machine;i++){
        for(int j=0;j<SA_vector[i].size();j++){
            cout << " " << setw(3) << SA_vector[i][j].getNo()
                << setw(7) << SA_vector[i][j].getTable()
                << setw(9) << SA_vector[i][j].getTimeR()
                << setw(9) << SA_vector[i][j].getMachineNo()
                << setw(7) << SA_vector[i][j].getTimeS()
                << setw(9) << SA_vector[i][j].getTimeP()
                << setw(10) << SA_vector[i][j].getTimeC()
                << setw(9) << SA_vector[i][j].getTimeW() << endl;}}
    cout << "Total Waiting Time : " << SA_totalWaiting << endl;
    cout << endl << endl;}


