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

class B{
    public:
        int n;
        B(int _n):n(_n){
            std::cout<<"con "<<n<<std::endl;
        }
        ~B(){
            std::cout<<"decon "<<n<<std::endl;
        }
};


int main(){
    A* p = new A();
    std::shared_ptr<A> ptr(p);
    std::shared_ptr<A> ptr2;
    // ptr2.reset(p); wrong, won't host p, shared_ptr will think, this "p" is diff from the  "p" above
    // and when the obj will be deconed, it will be deleted twice and causes problem

    std::shared_ptr<B> p_B(new B(1));
    p_B.reset(new B(2));            // reset第一种用法，先进行new B(2)，然后p_B对B(1)的引用减1，此时B(1)的引用为0
                                    // 会调用析构函数，然后再把新对象的指针交给智能指针托管
    ptr.reset();                    // reset的第二种用法，指针p的引用减少1
    return 0;
}