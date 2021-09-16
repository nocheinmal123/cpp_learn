#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
// keyowrd "nullptr"

int main(){
    int* p1 = NULL;
    int* p2 = nullptr;
    std::shared_ptr<double> ptr = nullptr;
    if(p1 == p2) std::cout<<"equal 1"<<std::endl;
    if(ptr == nullptr) std::cout<<"equal 2"<<std::endl;
    if(ptr == NULL) std::cout<<"equal 3"<<std::endl;
    return 0;
}