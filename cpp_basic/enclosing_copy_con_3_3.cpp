#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/*
class CTest{
    public:
        int n;
        CTest(int n):n(n){
            std::cout<<n<<" con called"<<std::endl;
        }
        ~CTest(){
            std::cout<<n<<" decon called"<<std::endl;
        }
};

CTest t1(1);

int main(){
    CTest t2(10);
    return 0;
}

Output:
1 con called
10 con called
10 decon called
1 decon called
*/

class A{
    public:
        A(){
            std::cout<<"default"<<std::endl;
        }
        A(const A &x){
            std::cout<<"copy"<<std::endl;
        }
};

class B{
    A a;
};

int main(){
    B b1;       //default
    B b2(b1);   //copy, when using copy con of b1, the b1.a will
    // also be copied, so the copy con of A will be excuted
    return 0;
}