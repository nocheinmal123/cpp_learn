#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// template func as friend of normal class

class A{
    private:
    int v;
    public:
        A(int n);
        template<class T>
        friend void Print(const T& p);
};

A::A(int n):v(n){

}

template<class T1>
void Print(const T1& p){
    std::cout<<p.v<<std::endl;
}


int main(){
    A a(10);
    Print(a);
    return 0;
}