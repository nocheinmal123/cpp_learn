#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
// if the throwed Exception is been catched and dealed with in the function,
// the Exception won't be throwed to the caller of the function

class CException{
    public:
        std::string msg;
        CException(std::string s):msg(s){

        }
};

double Devied(double x,double y){
    if(y == 0) throw CException("devied by zero"); // just throw an Exception, no more dealing
    // it will be dealed with in the main-func
    std::cout<<"in Devide"<<std::endl;
    return x/y;
}

int CountTax(int salary){
    try{
        if(salary < 0) throw -1;
        std::cout<<"counting tax"<<std::endl;
    }
    catch(int){
        std::cout<<"salary<0"<<std::endl;
    }
    std::cout<<"tax counted"<<std::endl;
    return salary*0.15;
}

int main(){
    double f = 1.2;
    try{
        CountTax(-1);
        f = Devied(3,0);
        std::cout<<"end of try block"<<std::endl;
    }
    catch(const CException& e){
        std::cout<<e.msg<<std::endl;
    }
    std::cout<<"f = "<<f<<std::endl;
    std::cout<<"finish"<<std::endl;
    return 0;
}