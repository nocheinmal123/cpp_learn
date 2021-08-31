#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// friends function: friends funtion of a obj, can visit the private var of obj
class CCar;

class CDriver{
    public:
        void ModifyCar(CCar * pcar);
};

class CCar{
    private:
        int price;
    friend int MostExpensiveCar(CCar cars[],int total); // friend functions are not member-func
    friend void CDriver::ModifyCar(CCar * pcar);
};

void CDriver::ModifyCar(CCar * pcar){
    pcar->price += 1000;
}

int MostExpensiveCar(CCar cars[],int total){
    int tmpMax = -1;
    for(int i=0;i<total;i++){
        // can vist the private var "price"
        if(cars[i].price > tmpMax) tmpMax = cars[i].price;
    }
    return tmpMax;
}

int main(){
    return 0;
}