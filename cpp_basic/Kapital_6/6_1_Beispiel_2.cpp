#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class base{
    public:
    virtual void f() const {
        std::cout<<"base f"<<std::endl;
    }
    void g() {
        std::cout<<"base g"<<std::endl;
    }
};

class D: public base{
    public:
    void f() const{
        std::cout<<"D f"<<std::endl;
    }
    void g() const{
        std::cout<<"D g"<<std::endl;
    }
};

class DD: public D{
    public:
    void f() const{
        std::cout<<"DD f"<<std::endl;
    }
    void g() const{
        std::cout<<"DD g"<<std::endl;
    }
};

class E: public DD{
    public:
    void f() {
        std::cout<<"E f"<<std::endl;
    }
    void g(){
        std::cout<<"E g"<<std::endl;
    }
};

void call(base &b){
    b.f();
    b.g();
}

int main(){
    base b;
    D d;
    DD dd;
    E e;

    call(b);
    call(d);
    call(dd);
    call(e); // if the polymorphsim is not applied in this class, 
    // this class will use its "nearest" class, in which polymorphsim is applied
    // d.g();
    // dd.g();

    return 0;
}

/*
base f
base g
D f
base g
DD f
base g
DD f
base g
*/