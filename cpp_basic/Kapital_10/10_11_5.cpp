#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
// out_of_range will be used to deal with vector of string, when using "at" function

int main(){
    std::vector<int> v(10);
    try{
        v.at(10) = 100;
    }
    catch(std::out_of_range& e){
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}