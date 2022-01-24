#include "13_brass.h"
const int CLIENTS = 2;

int main(){
    Brass* p_client[CLIENTS];
    std::string tempString;
    int tempNum;
    double tempBal;
    char kind;
    for(int i = 0; i < CLIENTS; i++){
        std::cout << "Enter the client's name: ";
        std::cin >> tempString;
        std::cout << "Enter client's account number: ";
        std::cin >> tempNum;
        std::cout << "Enter opening balance: " << std::endl;
        std::cin >> tempBal;
        std::cout << "Enter 1 for Brass Account or 2 for BrassPlus Account: ";
        while(std::cin >> kind && (kind != '1' && kind != '2'))
            std::cout << "Enter 1 or 2: ";
        if(kind == '1') p_client[i] = new Brass(tempString, tempNum, tempBal);
        else{
            double tempMax,tempRate;
            std::cout << "Enter the overdraft limit: ";
            std::cin >> tempMax;
            std::cout << "Enter the interest rate as a decimal fraction: ";
            std::cin >> tempRate;
            p_client[i] = new BrassPlus(tempString, tempNum, tempBal, tempMax, tempRate);
        }
        while(std::cin.get() != '\n') continue;
    }
    for(int i=0;i<CLIENTS;i++){
        p_client[i]->ViewAcct();
    }
    return 0;
}