#include <iostream>
#include <memory>
#include <string>

class B{
    public:
        int K;
        explicit B(int k = 0):K(k){

        }
        ~B() {}
};

class A{
    public:
        std::shared_ptr<B> p_b;
        A(){
            p_b = std::make_shared<B>();
        }
        std::shared_ptr<B>& getPB(){
            return p_b;
        }
        ~A() {}
};


int main(){
    std::shared_ptr<A> pA = std::make_shared<A>();
    (pA->getPB())->K = 101;
    std::cout << pA->p_b->K << std::endl;
    std::shared_ptr<B>& pB = pA->getPB();
    pB = std::make_shared<B>(1111);
    // pA->getPB() = std::make_shared<B>(1233);
    std::cout << pA->p_b->K << std::endl;

    return 0;
}