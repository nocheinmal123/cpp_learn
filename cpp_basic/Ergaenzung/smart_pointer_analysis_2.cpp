#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

class CT{
    public:
        std::shared_ptr<CT> getself(){
            return std::shared_ptr<CT>(this);
        }
};

class A: public std::enable_shared_from_this<A>{
    public:
        std::shared_ptr<A> getself(){
            return shared_from_this();
        }
};

class CA;
class CB;
class CA{
    public:
        std::shared_ptr<CB> m_pcb;
        ~CA(){
            std::cout<<"decon CA"<<std::endl;
        }
};

class CB{
    public:
        // std::shared_ptr<CA> m_pca;
        std::weak_ptr<CA> m_pca;
        ~CB(){
            std::cout<<"decon CB"<<std::endl;
        }
};

int main(){
    // 3.enable_from_this
    std::shared_ptr<CT> ptc1(new CT);
    std::shared_ptr<CT> ptc2 = ptc1;        //没有问题，两个强引用
    // 下面这个有问题，用了一个指针构造了两个智能指针，类似于之前的那个问题
    // std::shared_ptr<CT> ptc3 = ptc1->getself();
    // 应该使用类模板，enable_shared_from_this
    std::shared_ptr<A> ptc4(new A);
    std::shared_ptr<A> ptc5 = ptc4->getself();

    // 4.避免循环引用
    std::shared_ptr<CA> pca(new CA);
    std::shared_ptr<CB> pcb(new CB);
    pca->m_pcb = pcb;                       //等价于指向CB的对象有两个强引用
    pcb->m_pca = pca;                       //等价于指向CA的对象有两个强引用
    // 这两个引用计数都变成2了，离开作用域时，分别减1，并没有变成0，导致pca和pcb无法被释放
    // 应该将这两个类中，任意一个成员变量修改成weak_ptr
    // 因为m_pca是弱引用，所以指向CA对象的强引用只有1个，离开作用域时，pca引用计数变成0
    // CA被析构，导致CB对象的引用计数-1，离开作用域时，pcb引用计数再-1，CB被成功析构

    // 4.移动语义
    std::shared_ptr<int> p1(new int(100));
    std::cout<<p1.use_count()<<std::endl;
    std::shared_ptr<int> p2(std::move(p1));
    std::cout<<p2.use_count()<<std::endl;   //保持1不变，因为是移动，而不是复制
    return 0;
}