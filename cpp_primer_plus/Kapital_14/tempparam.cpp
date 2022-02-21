#include "stacktp.h"

// 模板类作为类模板参数
template <template<typename T> class Thing, typename T1, typename T2>
class Crab{
    private:
        Thing<T1> s1;
        Thing<T2> s2;
    public:
        Crab(int n): s1(n), s2(n) {};
        bool push(T1 a, T2 x);
        bool pop(){
            return s1.pop() && s2.pop();
        }
};

template<template<typename T> class Thing, typename T1, typename T2>
bool Crab<Thing, T1, T2>::push(T1 a, T2 x){
    return s1.push(a) && s2.push(x);
}

int main(){
    Crab<Stack, int, double> nebula(3);
    int a;
    double x;
    int k = 3;
    while(k--){
        std::cin >> a;
        std::cin >> x;
        std::cout << nebula.push(a, x) << std::endl;
    }
    return 0;
}