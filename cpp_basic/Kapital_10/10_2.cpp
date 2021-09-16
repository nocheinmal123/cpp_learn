#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// keyword "decltype"
// decltype(exp)

struct A{
    double x;
};

int i;
double t;
const int m = 0;
const A* a = new A();
int& ref = i;


int main(){
    decltype(a) x1; std::cout<<typeid(x1).name()<<std::endl;
    decltype(i) x2; std::cout<<typeid(x2).name()<<std::endl;
    decltype(a->x) x3; std::cout<<typeid(x3).name()<<std::endl;         // x3 is double
    decltype((a->x)) x4 = t; std::cout<<typeid(x4).name()<<std::endl;   // x4 is double&
    decltype(m) p = 100; std::cout<<typeid(p).name()<<std::endl;
    decltype(ref) k = i; std::cout<<typeid(k).name()<<std::endl;
    return 0;
}