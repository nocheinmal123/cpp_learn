#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
// 函数模板特例化（具体化），目的是因为有的时候不同的类型会采用不同的数据处理方法
// 函数模板实例化
/*
在代码中包含函数模板本身并不会生成函数定义，它只是一个用于生成函数定义的
解决方案。编译器使用模板为特定类型生成函数定义时，得到的是模板实例。比如
直接调用Swap，那么针对具体数据类型，就会有一个实例出现，这种实例化方式
叫作隐式实例化。
*/

struct Node{
    int x;
    int y;
    Node(int _x, int _y):x(_x),y(_y){};
};

template <typename T>
void Swap(T& a,T& b){
    T temp = a;
    a = b;
    b = temp;
    return;
}

// explicit specialization
template<>
void Swap(Node& a, Node& b){
    int temp_x = a.x;
    a.x = b.x;
    b.x = temp_x;

    int temp_y = a.y;
    a.y = b.y;
    b.y = temp_y;
    return;
}


int main(){
    int x = 10, y = 20;
    Node node_1(1,2);
    Node node_2(3,4);
    Swap(x, y);
    std::cout << x << ", " << y << std::endl;
    Swap(node_1, node_2);
    std::cout << "node_1.x = " << node_1.x << ", node_1.y = " << node_1.y << std::endl;
    std::cout << "node_2.x = " << node_2.x << ", node_2.y = " << node_2.y << std::endl;
    return 0;
}