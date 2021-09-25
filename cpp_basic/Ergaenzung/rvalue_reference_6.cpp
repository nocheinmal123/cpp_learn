#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

class mynum{
    public:
        int num1; int num2;
        mynum(int x = 0,int y = 0):num1(x),num2(y){
            std::cout<<"con called "<<num1<<", "<<num2<<std::endl;
        }
        mynum(const mynum& t){
            this->num1 = t.num1;
            this->num2 = t.num2;
            std::cout<<"copy con called "<<num1<<", "<<num2<<std::endl;
        }
        virtual ~mynum(){
            std::cout<<"decon "<<num1<<", "<<num2<<std::endl;
        }
};

mynum operator+(const mynum& x,const mynum& y){
    return mynum(x.num1 + y.num1, x.num2 + y.num2);
}

int main(){
    // 4.类外的运算符的重载会产生临时对象
    mynum x;
    x.num1 = 10;
    x.num2 = 12;
    mynum y;
    y.num1 = 7;
    y.num2 = 3;
    mynum res(x+y);
    return 0;
}
/*
con called 0, 0
con called 0, 0
con called 17, 15
copy con called 17, 15
decon 17, 15
copy con called 17, 15
decon 17, 15
decon 17, 15
decon 7, 3
decon 10, 12
*/