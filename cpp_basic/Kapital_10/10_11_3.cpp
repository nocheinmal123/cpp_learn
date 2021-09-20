#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
// exception class in C++11
// bad_typeid, bad_cast, bad_alloc, ios_base::failure, logic_error------->out_of_range
// bad_cast will be used, when using dynamic_cast to change the ref of base-class (polymorphism)
// to the ref of derived calss

class base{
    public:
        virtual void func();
};

class Derived: public base{
    public:
        void Print(){
            std::cout<<"Derived Print called"<<std::endl;
        }
};

void PrintObj(base& b){
    try{
        Derived& rd = dynamic_cast<Derived&>(b);
        rd.Print();
    }
    catch(std::bad_cast& e){
        std::cerr<<e.what()<<std::endl;
    }
};

int main(){
    base b;
    PrintObj(b);
    return 0;
}