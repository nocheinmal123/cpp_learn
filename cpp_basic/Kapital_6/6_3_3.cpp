#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

class base{
    public:
        void fun1(){
            fun2(); // <==> this->fun2(), cauz fun2() is virtual, it is polyporphsim 
        }
        virtual void fun2(){
            std::cout<<"Base::fun2()"<<std::endl;
        }
};

class derived: public base{
    public:
        virtual void fun2(){
            std::cout<<"Derived::fun2()"<<std::endl;
        }
};

int main(){
    derived d;
    base* p = &d;
    p->fun1();
    d.fun1();
    d.base::fun1();
    return 0;
}

/*
Derived::fun2()
Derived::fun2()
Derived::fun2()

So we can get, in the member func (no con func and no decon func),
when we call virtual func, it is polymorphsim
*/