#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
// dynamic_cast, used to change the class-base-pointer to derived-class-pointer (must when polymorphism)
// if unsafe, return NULL

class Base{
    public:
        virtual ~Base(){

        }
};

class Dearived: public Base{

};

int main(){
    Base b;
    Dearived d;
    Dearived* pd;
    pd = reinterpret_cast<Dearived*>(&b); // pd is now points at base class
    pd = dynamic_cast<Dearived*>(&b);
    if(pd == NULL) std::cout<<"unsafe1"<<std::endl;
    Base* pb = &d;
    pb = dynamic_cast<Dearived*>(&d);
    if(pb == NULL) std::cout<<"unsafe2"<<std::endl;
    return 0;
}
