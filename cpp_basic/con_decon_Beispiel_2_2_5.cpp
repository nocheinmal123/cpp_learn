#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class A{
    public:
        int x;
        A(int x_):x(x_){
            std::cout<<x<<" con called"<<std::endl;
        }
        A(const A &a){
            x = 2 + a.x;
            std::cout<<"copy called"<<std::endl;
        }
        ~A(){
            std::cout<<x<<" decon called"<<std::endl;
        }
};

A func(){
    A b(10);
    return b;
}

int main(){
    A a(1);
    a = func();
    return 0;
}

/*
standard C++ compiler:
1 con called    // a con
10 con called   // b con
10 decon called // b decon
copy called     // the temp-value is created by copy
12 decon called // the temp-value decon
12 decon called // a decon 
*/