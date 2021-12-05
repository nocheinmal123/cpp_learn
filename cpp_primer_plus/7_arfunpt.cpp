#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

const double* f1(const double* ar, int n){
    return ar;
}

const double* f2(const double ar[], int n){
    return ar + 1;
}

const double* f3(const double ar[], int n){
    return ar + 2;
}

int main(){
    double av[3] = {1112.3, 1542.6, 2227.9};
    const double* (*p1)(const double* ,int) = f1;
    auto p2 = f2;
    std::cout << (*p1)(av,3) << ": " << *((*p1)(av,3)) << std::endl;
    std::cout << p2(av,3) << ": " << *(p2(av,3)) << std::endl;
    std::cout << std::endl;

    // an array of pointer-to-function
    const double* (*pa[3])(const double*,int) = {f1, f2, f3}; 
    // pb a pointer to first element of pa
    auto pb = pa;
    for(int i=0;i<3;i++) std::cout << (*pa[i])(av,3) << ": " << *((*pa[i])(av,3)) << std::endl;
    for(int i=0;i<3;i++) std::cout << (*pb[i])(av,3) << ": " << *((*pb[i])(av,3)) << std::endl;
    return 0;
}