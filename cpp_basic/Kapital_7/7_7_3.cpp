#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>

class A{
    public:
        int v1;
};

template <class T>
class B: public A{ // derived from a normal class
    public:
        T v1;
};

int main(){
    B<char> obj;
    std::cout<<typeid(obj.v1).name()<<std::endl;
    std::cout<<typeid(obj.A::v1).name()<<std::endl;
    return 0;
}