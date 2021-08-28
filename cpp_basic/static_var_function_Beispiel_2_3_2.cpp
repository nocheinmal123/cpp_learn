#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Budget{
    private:
        static double corpBudget;
        double divBudget;
    public:
        Budget();
        void addBudget(double v);
        double getDivBudget() const;
        double getCorpBudget() const;
};

Budget::Budget(){
    divBudget = 0;
}

void Budget::addBudget(double v){
    divBudget += v;
    corpBudget += divBudget;
}

double Budget::getDivBudget() const{
    return divBudget;
}

double Budget::getCorpBudget() const{
    return corpBudget;
}

double Budget::corpBudget = 0;

int main(){
    Budget b1;
    b1.addBudget(10.1);
    printf("%.2lf\n",b1.getDivBudget());
    printf("%.2lf\n",b1.getCorpBudget());

    Budget b2;
    b2.addBudget(20.3);
    printf("%.2lf\n",b2.getDivBudget());
    printf("%.2lf\n",b2.getCorpBudget());
    return 0;
}