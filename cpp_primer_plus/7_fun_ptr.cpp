#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
/*
7.18 fun_ptr.cpp
设计一个名为estimate()的函数，估算编写指定代码行数的时间，不同程序员将采用不同的估算方法
因此，这个函数必须能够接收不同的函数
*/

double cal1(int lines){
    return 0.03 * lines;
}

double cal2(int lines){
    return 0.05 * lines + 0.0004 * lines * lines;
}

double estimate(int lines, double cal(int)){
    return cal(lines);
}

// 下面这种也正确，在函数指针中，往往函数指针就是函数名，是等价的
double estimate_tranform(int lines, double (*cal)(int)){
    // return (*cal)(lines);
    return cal(lines);
}

int main(){
    int n;
    std::cin >> n;
    std::cout << estimate(n,cal1) << std::endl;
    std::cout << estimate(n,cal2) << std::endl; 
    std::cout << estimate_tranform(n,cal1) << std::endl;
    std::cout << estimate_tranform(n,cal2) << std::endl;
    return 0;
}