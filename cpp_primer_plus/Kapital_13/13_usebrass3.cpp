#include "13_acctabc.h"
#include <iostream>
#include <string>
const int CLIENTS = 2;
using std::cout;
using std::cin;
using std::endl;

int main(){
    using pAccABC = AcctABC*;
    pAccABC* p_client = new pAccABC[CLIENTS];
    std::string tempString;
    int tempNum;
    double tempBal;
    int kind;
    for(int i=0;i<CLIENTS;i++){
        cout << "Enter client's name: ";
        cin >> tempString;
        cout << "Enter client's account number: ";
        cin >> tempNum;
        cout << "Enter opening balance: ";
        cin >> tempBal;
        cout << "Enter 1 for Brass Account or 2 for BrassPlus Account:";
        while(cin >> kind && (kind != 1 && kind != 2)){
            cout << "Enter either 1 or 2: ";
        }
        if(kind == 1){
            p_client[i] = new Brass(tempString, tempNum, tempBal);
        }
        else{
            double tempMax, tempRate;
            cout << "Enter the overdraft limit: ";
            cin >> tempMax;
            cout << "Enter the inerest rate as a decimal fraction: ";
            cin >> tempRate;
            p_client[i] = new BrassPlus(tempString, tempNum, tempBal, tempMax, tempRate);
        }
    }
    for(int i=0;i<CLIENTS;i++){
        p_client[i]->ViewAcct();
        cout << endl;
    }
    for(int i=0;i<CLIENTS;i++) delete p_client[i];
    delete p_client;
    return 0;
}