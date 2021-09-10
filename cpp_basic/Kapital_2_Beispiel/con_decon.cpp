#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class A{
    private:
        int x;
    public:
        explicit A(int _x):x(_x){
            std::cout<<x<<" con called"<<std::endl;
        }
        A(const A& a){
            x = a.x*2;
            std::cout<<x<<" copy con called"<<std::endl;
        }
        ~A(){
            std::cout<<x<<" decon called"<<std::endl;
        }
};

A func(A c){
    A a(10);
    return a;
}
// decon sequence:
// first local var, then the temp value(return value),
// then par of func, then par of fun int main, then A
// We can also think in this way: firstly the local var of func
// then according to the sequence of generation(late first, earlier after)

int main(){
    A a(100);
    a = func(A(7));
    return 0;
}
/*
100 con called
7 con called -------> A(7)
14 copy con called -> A c
10 con called ------> A a(10)
20 copy con called -> A func(...)
10 decon called ----> A a(10)
20 decon called ----> A func(...)
14 decon called ----> A c
7 decon called -----> A(7)
20 decon called
*/