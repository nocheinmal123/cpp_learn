#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Base{
    public:
        int n;
        Base(int i):n(i){
            std::cout<<"Base "<<n<<" con called"<<std::endl;
        }
        ~Base(){
            std::cout<<"Base "<<n<<" decon called"<<std::endl;
        }
};

class Derived: public Base{
    public:
        Derived(int i):Base(i){
            std::cout<<"Derived con called"<<std::endl;
        }
        ~Derived(){
            std::cout<<"Derived decon called"<<std::endl;
        }
};

class MoreDerived: public Derived{
    public:
        MoreDerived():Derived(4){
            std::cout<<"MoreDerived con called"<<std::endl;
        }
        ~MoreDerived(){
            std::cout<<"MoreDerived decon called"<<std::endl;
        }
};

int main(){
    MoreDerived obj;
    return 0;
}

/*
Base 4 con called
Derived con called
MoreDerived con called
MoreDerived decon called
Derived decon called
Base 4 decon called
*/
// just like the process of the recursive