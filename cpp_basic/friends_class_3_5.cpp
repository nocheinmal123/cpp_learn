#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// friend class: if A is the friend class of B, the member func of A can visit
// private vars of B
// the relation of friend class, can't be passed,can't be inheritanced
class CCar{
    private:
        int price;
    public:
        explicit CCar(int n){
            price = n;
        }
    friend class CDriver; // declaration of CDriver as friend class
    // so the objs of CDriver can visit price
};

class CDriver{
    public:
        CCar mycar;
        CDriver(int n):mycar(10){};
        void ModifyCar(){
            mycar.price += 1000;
        }
        void Print(){
            printf("%d\n",mycar.price);
        }
};

int main(){
    CDriver driver(10);
    driver.ModifyCar();
    driver.Print();
    return 0;
}