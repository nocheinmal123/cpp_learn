#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// template class derived from template class
template <class T1, class T2>
class A{
    public:
    T1 v1;
    T2 v2;
};

template <class T3, class T4>
class B: public A<T4, T3>{
    public:
    T3 v3;
    T4 v4;
};

template <class T>
class C: public B<T, T>{
    public:
    T v1;
};

int main(){
    B<int, double> obj1;
    std::cout<<typeid(obj1.v3).name()<<std::endl;
    std::cout<<typeid(obj1.v4).name()<<std::endl;
    std::cout<<typeid(obj1.v1).name()<<std::endl;
    std::cout<<typeid(obj1.v2).name()<<std::endl;
    /*
    Output:
    i
    d
    d
    i
    */
    std::cout<<"---------------------"<<std::endl;
    C<int> obj2;
    std::cout<<typeid(obj2.A<int,int>::v1).name()<<std::endl;
    std::cout<<typeid(obj2.v1).name()<<std::endl;
    return 0;
}