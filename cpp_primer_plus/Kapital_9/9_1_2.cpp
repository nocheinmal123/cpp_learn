#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
/*
声明区域 declaration region 和
潜在作用域 potential scope
delcaration region:
在函数外声明全局变量，对于这种变量，声明区域为所在的文件；对于函数
中的声明的变量，声明区域为其声明所在的代码块
potential scope:
变量的潜在作用域从声明点开始，到其声明区域的结尾。因此潜在作用域比
声明区域小，因为变量必须在定义后才能使用

命名空间 namespace:
实际上是一种新的声明区域，通过这个新的声明区域来创建命名的名称空间。
这样做的目的之一是提供一个声明名称的区域
命名空间可以是全局的，也可以位于另外一个命名空间中，但不能位于代码
块中。
*/

namespace Jill{
    double bucket(double n);
    double fetch;
    struct Hill{};
}

using Jill::fetch;          //put fetch into global namespace

void other(){
    std::cin >> fetch;      //read a value into Jill::fetch
}

int main(){
    std::cout << fetch;
    return 0;
}