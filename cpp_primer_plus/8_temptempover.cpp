#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

// template A
template <typename T>
void ShowArray(T arr[], int n){     
    for(int i=0;i<n;i++){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// template B
template <typename T>
void ShowArray(T* arr[], int n){
    for(int i=0;i<n;i++){
        std::cout << *arr[i] << " ";
    }
    std::cout << std::endl;
}

struct debts{
    char names[30];
    double amout;
};

int main(){
    int things[6] = {13, 31, 103, 301, 310, 130};
    struct debts mr_E[3] = {
        {"Ima Wolfe", 2400.0},
        {"Ura Foxe", 1300.0},
        {"Iby Stout", 1800.0}
    };
    double* pd[3];
    for(int i=0;i<3;i++) pd[i] = &mr_E[i].amout;
    std::cout << "Listing Mr. E's counts of things:\n";
    ShowArray(things, 6);   // use template A
    std::cout << "Listing Mr. E's debts:\n";
    ShowArray(pd, 3);       // use template B
    // 如果把template B删除，那么调用ShowArray(pd, 3)的时候，将采用template A,
    // 打印出来的就是地址，而不是值
    return 0;
}