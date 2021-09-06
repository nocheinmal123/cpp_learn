#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class A{
    public:
        virtual void Print(){
            printf("A\n");
        }
};

class B: public A{
    public:
        virtual void Print(){
            printf("B\n");
        }
};

class D: public A{
    public:
        virtual void Print(){
            printf("D\n");
        }
};

class E: public B{
    public:
        virtual void Print(){
            printf("E\n");
        }
};

int main(){
    A a;
    B b;
    E e;
    D d;
    A *pa = &a;
    B *pb = &b;
    D *pd = &d;
    E *pe = &e; // E is the indirect son class of class A

    pa->Print();
    pa = pb;
    pa->Print();
    pa = pd;
    pa->Print();
    pa = pe;
    pa->Print();
    /*
    A
    B
    D
    E
    */
    return 0;
}