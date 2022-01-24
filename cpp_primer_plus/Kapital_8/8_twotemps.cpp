#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
// 函数模板的重载

template <class T>
void Swap(T& a, T& b){
    std::cout << "1" << std::endl;
    T temp = a;
    a = b;
    b = temp;
    return;
}

template <class T>
void Swap(std::shared_ptr<T>& ptr1, std::shared_ptr<T>& ptr2){
    std::cout << "2" << std::endl;
    std::swap(ptr1, ptr2);
    return;
}

int main(){
    int x = 10, y = 20;
    Swap(x, y);
    std::shared_ptr<std::string> ptr1 = std::make_shared<std::string>("fangsen");
    std::shared_ptr<std::string> ptr2 = std::make_shared<std::string>("yilin");
    Swap(ptr1, ptr2);
    std::cout << x << ", " << y << std::endl;
    std::cout << *ptr1 << ", " << *ptr2 << std::endl;
    return 0;
}