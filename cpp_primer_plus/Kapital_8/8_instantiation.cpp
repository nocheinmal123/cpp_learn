#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

struct Node
{
    int x;
    int y;
    Node(int _x, int _y):x(_x),y(_y){};
    void Print(){
        std::cout << "x = " << x << ", y = " << y <<std::endl;
    }
};


template <typename T>
T Add(T a, T b){
    return a + b;
}

template <>
Node Add(Node a, Node b){
    return Node(a.x + b.x, a.y + b.y); 
}

// explicit template instantiation 
// 这些声明的意思是：不要使用 Add() 模板来生成函数定义，而应该使用专门为 double 类型显式定义的函数定义。
// 这些原型必须有自己的函数定义。
template double Add<double>(double, double);
// template double Add<double>(double a, double b); it also works

int main(){
    int x = 10, y = 20;
    printf("res = %d\n",Add(x, y));
    Node node_1(1, 2);
    Node node_2(3, 4);
    Node res = Add(node_1, node_2);
    res.Print();
    double m = 10;
    double n = 3.4;
    printf("res = %.2lf\n", Add(m, n));
    return 0;
}