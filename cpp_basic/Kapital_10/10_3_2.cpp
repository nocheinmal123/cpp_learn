#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
class A{
    public:
        ~A(){
            std::cout<<"decon"<<std::endl;
        }
};


int main(){
    A* p = new A();
    std::shared_ptr<A> ptr(p);
    std::shared_ptr<A> ptr2;
    // ptr2.reset(p); wrong, won't host p, shared_ptr will think, this "p" is diff from the  "p" above
    // and when the obj will be deconed, it will be deleted twice and causes problem
    return 0;
}