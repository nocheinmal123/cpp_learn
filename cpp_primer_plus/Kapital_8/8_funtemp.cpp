#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
// 函数模板
template <class T>
void Swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
}

int main(){
    int i = 10, j = 20;
    double x = 1.3, y = 2.7;
    Swap(i ,j);
    Swap(x, y);
    std::cout << "now i = " << i << ", j = " << j << std::endl;
    std::cout << "now x = " << x << ", y = " << y << std::endl;
    return 0;
}