#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
// pure virtual func and abstract class
// if the class included the pure virtual func, it is so called abstract class
// abstract class can only be base class, the obj of this abstract class can not be created individuell
// the obj of abstract class can only be included in a obj of derived class
// if a class is a derived class of a abstract class, only when he has
// realized all pure virtual funcs, then it doesn't belong to abstract class
class A{
    private:
        int a;
    public:
        virtual void f() = 0; // pure virtual func
        void g(){
            f();
        }
        A(){

        }
};

class B: public A{
    public:
        void f(){
            std::cout<<"B::f()"<<std::endl;
        }
};

int main(){
    B b;
    b.g();
    A* p = new B();
    p->g();
    p->f();
    return 0;
}