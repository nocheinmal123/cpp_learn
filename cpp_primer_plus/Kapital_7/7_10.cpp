#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

double add(double x, double y){
    return x + y;
}

double minus(double x, double y){
    return x - y;
}

double multiply(double x, double y){
    return x * y;
}

double divide(double x, double y){
    return x / y;
}

double calculate(double x, double y, double (*operation)(double, double)){
    return (*operation)(x,y);
}

int main(){
    double (*p[4])(double, double) = {add, minus, multiply, divide};
    double x = 3.2, y = 1.7;
    for(int i=0;i<4;i++){
        // 调用的时候是需要像一个调用参数一样，调用函数指针
        std::cout << calculate(x, y, (*p[i])) << std::endl;
    }
    return 0;
}