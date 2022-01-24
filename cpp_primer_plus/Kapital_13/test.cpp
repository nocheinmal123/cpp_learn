#include <iostream>
#include <string>
#include <string.h>

class A{
    public:
        A(){

        }
        virtual void func1(int n);
};

void A::func1(int n){
    std::cout << "A func1" << std::endl;
}

class B: public A{
    public:
        B():A(){

        }
        void funcB();
        virtual void func1();
};

void B::funcB(){
    std::cout << "B funcB" << std::endl;
}

void B::func1(){
    std::cout << "B func1" << std::endl;
}

// void B::func2(){
// }

int main(){
    A* p = new B();
    p->func1(78);
    p->A::func1(20);
    // p->func1(); p指针失去了多态的特性
    B obj_B;
    obj_B.A::func1(3);
    obj_B.funcB();
    return 0;
}