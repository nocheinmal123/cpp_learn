#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>

template <class T>
class A{
    public:
        T v1;
        int n;
};

class B: public A<char>{
    public:
        double v1;
};

int main(){
    B obj;
    std::cout<<typeid(obj.v1).name()<<std::endl;
    std::cout<<typeid(obj.A::n).name()<<std::endl;
    std::cout<<typeid(obj.A::v1).name()<<std::endl;
    return 0;
}