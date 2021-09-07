#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

class A{
    public:
        virtual void Func(){
            std::cout<<"A::Func"<<std::endl;
        }
};

class B: public A{
    public:
        virtual void Func(){
            std::cout<<"B::Func"<<std::endl;
        }
};

int main(){
    // if the class has a virtual func, then its obj has 4 (or 8) more bytes
    // to store a pointer, which points at the V-Talble
    A a;
    A* pa = new B();
    pa->Func();
    long long* p1 = (long long*) &a;
    long long* p2 = (long long*) pa;
    // *p1 <==> the adresse of the V-Table of class A
    // *p2 <==> the asresse of the V-Talbe of class B
    *p2 = *p1; // use a pointer, which points at the pointer pa, to change the pointer pa
    pa->Func();
    return 0;
}