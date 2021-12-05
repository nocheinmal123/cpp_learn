#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
T lesser(T a, T b){         // #1
    return a < b ? a : b;
}

int lesser(int a, int b){   // #2
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    return a < b ? a : b;
}

// 关键字decltype
template <typename T1, typename T2>
void ft(T1 x, T2 y){
    typedef decltype(x + y) res;
    res sum = x + y;
    res arr[10];
    res& arr_ref = arr[1];
    return;
}

// 有返回值的时候，可以这样使用,C++11后置返回类型
template <typename T1, typename T2>
auto gt(T1 x, T2 y) -> decltype(x + y){
    return x + y;
}

int main(){
    int m = 20, n = -30;
    double x = 15.5, y = 25.9;
    std::cout << lesser(m, n) << std::endl;     // #2
    std::cout << lesser(x, y) << std::endl;     // #1 with double
    std::cout << lesser<>(m, n) << std::endl;   // #1 with int,lesser<>提醒编译器，应该选择一个模板函数
    std::cout << lesser<int>(x, y) << std::endl;    // #1 with int

    std::cout << "--------------decltype---------------" << std::endl;
    int t = 10;
    decltype(t) y = 100;    // make y the same type as x
    decltype(t + y) z;      // make z the same type as x + y
    int& r = t;
    int p = 101;
    decltype(r) ref_var_1 = p;      //ref
    decltype((t)) ref_var_2 = p;    //also ref

    return 0;
}