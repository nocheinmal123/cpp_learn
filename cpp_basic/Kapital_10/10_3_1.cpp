#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
// shared_ptr
// shared_ptr<T> ptr (new T)
class A{
    private:
        int n;
    public:
        A(int v = 0);
        ~A();
        void Print();
        int& reset_var();
};

A::A(int v):n(v){

}

A::~A(){
    std::cout<<"decon called"<<std::endl;
}

void A::Print(){
    std::cout<<"n = "<<n<<std::endl;
}

int& A::reset_var(){
    return n;
}

int main(){
    std::shared_ptr<A> sp1(new A(2)); sp1->Print(); // sp1 and sp2 will always points at the same obj
    std::shared_ptr<A> sp2(sp1); sp2->Print();
    std::shared_ptr<A> sp3;
    sp1->reset_var() = 10; sp1->Print();
    sp2->Print();
    A* p = sp1.get(); p->Print();
    sp3 = sp1; sp3->Print();
    sp1.reset(); // abort 
    if(!sp1) std::cout<<"sp1 is null"<<std::endl;

    A* q = new A(3);
    sp1.reset(q); // sp1 is now hosting the pointer q; 
    sp1->Print();
    std::shared_ptr<A> sp4(sp1); // sp4 is now also hosting the pointer q;
    std::shared_ptr<A> sp5;
    // sp5.reset(q); wrong
    sp1.reset(); // abort hosting A(3)
    sp4.reset(); // abort hosting A(3), and now no shared_prt hosts A(3), decon will be called

    std::cout<<"-----------------------"<<std::endl;
    class A* p1 = new A(7);
    class A* p2 = p1;
    p1->Print();
    p2->Print();
    p2 = new A(67);
    p2->Print();
    p1->Print();
    std::cout<<"-----------------------"<<std::endl;
    return 0;
}