#include "9_namesp.h"
#include <iostream>

void other(){
    using namespace debts;
    Debt sample("sen", "fang", 10);
    sample.showDebt();
    sample.setDebt();
    sample.showDebt();

    Debt zippy[3];
    for(int i=0;i<3;i++){
        zippy[i].setDebt();
    }
    for(int i=0;i<3;i++){
        zippy[i].showDebt();
    }
    std::cout << "sum Debt: " << sumDebt(zippy, 3) << std::endl;
}

void another(){
    using pers::Person;
    Person collector = {"sen", "fang"};
    collector.showPerson();
}

int main(){
    other();
    another();
    return 0;
}