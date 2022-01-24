#include "9_namesp.h"
#include <iostream>

namespace pers{
    void Person::setPerson(){
        std::cout << "Enter first name: ";
        std::cin >> fname;
        std::cout << "Enter last name: ";
        std::cin >> lname;
    }
    void Person::showPerson() const{
        std::cout << lname << ", " << fname << std::endl;
    }
}

namespace debts{
    // void getDebt(Debt& rd){
    //     getPerson(rd.name);
    //     std::cout << "Enter Debt: ";
    //     std::cin >> rd.amount;
    // }
    // void showDebt(const Debt& rd){
    //     showPerson(rd.name);
    //     std::cout << ": $" << rd.amount << std::endl;
    // }
    // double sumDebt(const Debt* ar, int n){
    //     double sum = 0;
    //     for(int i=0;i<n;i++) sum += ar[i].amount;
    //     return sum;
    // }
    double sumDebt(const Debt* arr, int n){
        double sum = 0;
        for(int i=0;i<n;i++) sum += arr[i].amount;
        return sum;
    }
    void Debt::setDebt(){
        name.setPerson();
        std::cout << "Enter Debt: ";
        std::cin >> amount;
    }
    void Debt::showDebt() const{
        name.showPerson();
        std::cout << "Debt: " << amount << std::endl;
    }

}