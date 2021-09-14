#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>

template <class T1, class T2>
class A{
    public:
    T1 v1;
    T2 v2;
};

template <class T>
class B: public A<int, double>{  // derived fromr a "already realized" template class
    public:
    T v;
};


int main(){
    B<char> obj1;
    std::cout<<typeid(obj1.A<int,double>::v1).name()<<std::endl;
    std::cout<<typeid(obj1.A<int,double>::v2).name()<<std::endl;
    std::cout<<typeid(obj1.v).name()<<std::endl;
    return 0;
}
