#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
// bad_alloc when using "new" to allocate the ROM, 
// if the requirement is too big, it will throw exception



int main(){
    try{
        char* p = new char[0x7fffffffff]; //can't allocate so much
    }
    catch(std::bad_alloc& e){
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}