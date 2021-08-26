#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class CMyclass{
    public:
        CMyclass(){
            std::cout<<"con"<<std::endl;
        }
        ~CMyclass(){
            std::cout<<"destructor"<<std::endl;
        }
};

CMyclass obj; // con
CMyclass fun(CMyclass sobj){ // the death of sobj will also leads to decon
    return sobj; //return the temp value
}

int main(){
    obj = fun(obj); //con and decon of fun(obj), decon of this temp-value will
    // occurs when this statement ends
    return 0;
}

/*
con
con
decon
con
decon
decon
*/