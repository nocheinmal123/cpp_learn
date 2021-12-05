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
T Maxn(T* arr,int n){
    T _max = arr[0];
    for(int i=0;i<n;i++) _max = std::max(_max, arr[i]);
    return _max;
}

template <>
char* Maxn(char** arr, int n){
    char* s = arr[0];
    int _max = strlen(s);
    for(int i=0;i<n;i++){
        int len = strlen(s);
        if(len > _max){
            _max = len;
            s = arr[i];
        }
    }
    return s;
}

int main(){
    int arr_int[5] = {-1,4,2,0,17};
    double arr_double[3] = {1.3, 4.2, 2.6};
    std::cout << Maxn(arr_int, 5) << std::endl;
    std::cout << Maxn(arr_double, 3) << std::endl;
    return 0;
}