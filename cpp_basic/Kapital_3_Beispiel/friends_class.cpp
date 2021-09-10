#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// friend class
// friend function
// friend member-func
class A{
    private:
        int data;
    friend class B; //class B can now visit the private member-var
    // of class A, but it is single-direction, which means, class A
    // still can't visit the member-var of class B
};

class C;

class B{
    public:
        void CallBAF(int x,A& a){
            a.data = x;
            std::cout<<a.data<<std::endl;
        }
        void CallCAF(int x,C& c);
        void Print(){
            std::cout<<"fff"<<std::endl;
        }
};


class C{
    private:
        int data;
    public:
        C(int d = 0):data(d){

        }
    friend void B::CallCAF(int x, C& c); //friend member-func
};

// must code here, cauze the class C must be defined firstly,
// pls pay attention of the position of the friend member-func
void B::CallCAF(int x, C& c){
    c.data = 2*x;
    std::cout<<c.data<<std::endl;
}

int main(){
    A a;
    B b;
    b.CallBAF(10,a);
    C c(100);
    b.CallCAF(8,c);
    return 0;
}