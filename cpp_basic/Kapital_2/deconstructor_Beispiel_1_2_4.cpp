#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class CMyclass{
    private:
        int n;
    public:
        CMyclass(int x):n(x){
            std::cout<<n<<" con"<<std::endl;
        }
        CMyclass(const CMyclass& c){
            n = 2*c.n;
            std::cout<<n<<" copy con"<<std::endl;
        }
        ~CMyclass(){
            std::cout<<n<<" destructor"<<std::endl;
        }
};

CMyclass obj(10); // con
CMyclass fun(CMyclass sobj){ // the death of sobj will also leads to decon
    return sobj; //return the temp value
}

int main(){
    obj = fun(obj); //con and decon of fun(obj), decon of this temp-value will
    // occurs when this statement ends
    return 0;
}

/*
10 con
20 copy con
40 copy con
40 destructor
20 destructor
40 destructor
*/