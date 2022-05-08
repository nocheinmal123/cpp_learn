#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <thread>


class Sample {
    private:
        int m_;
    public:
        explicit Sample(int m): m_(m) {
           std::cout << "con called.\n"; 
        }
        Sample(const Sample& src) {
            m_ = src.m_;
            std::cout << "copy con called.\n";
        }
        Sample(Sample&& src) {
            m_ = src.m_;
            src.m_ = 0;
            std::cout << "move con called.\n";
        }
};


Sample return_sample() {
    Sample x(10);
    return x;
}

int main(){
    // 这种返回临时对象的函数会调用移动构造函数,如果没有移动构造，会调用拷贝构造
    Sample t = return_sample();
    return 0;
}