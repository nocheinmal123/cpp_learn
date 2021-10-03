#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

class A{
    public:
        int n;
        A(int _n):n(_n){
            std::cout<<"A con called "<<n<<std::endl;
        }
        ~A(){
            std::cout<<"A decon called "<<n<<std::endl;
        }
        void Print(){
            std::cout<<"n = "<<n<<std::endl;
        }
};

std::shared_ptr<A> create(int value){
    return std::make_shared<A>(value);
}

void myfunc1(int val){
    std::shared_ptr<A> tmp = create(val);
    return;
}

std::shared_ptr<A> myfunc2(int val){
    std::shared_ptr<A> p(new A(12));
    // return std::shared_ptr<A>(new A(12));        带返回值函数不同写法
    // return std::make_shared<A>(12);              带返回值函数不同写法
    return create(val);             //这个return会导致引用计数+1
}

void proc(std::shared_ptr<A> p){
    std::cout<<"in proc"<<std::endl;
    p->Print();
    return;
}

int main(){
    auto p = create(10);
    p->Print();
    myfunc1(12);
    myfunc2(79);                                //没有接受返回值，返回的share_ptr被销毁，指向的对象也会被销毁
    auto p_2 = myfunc2(77);                     //接收返回值，返回的share_ptr不被销毁，指向的对象也不会被销毁
    std::cout<<p_2.use_count()<<std::endl;

    // 1.慎用裸指针
    A* p_3 = new A(15);
    proc(std::shared_ptr<A>(p_3));              //显式地声明
    // p_3 = new A(20);                         再次修改p_3会导致难以预料的
    // 应该如以下使用
    std::shared_ptr<A> p_A = std::make_shared<A>(15);
    proc(p_A);
    p_A = std::make_shared<A>(20);
    // 同时需要注意，一个裸指针只能初始化一个智能指针
    std::shared_ptr<A> p_A_1(p_3);
    // std::shared_ptr<A> p_A_2(p_3); 错误，释放的时候p_3指向的内存会被释放两次，导致错误

    // 2.慎用get返回的指针
    std::shared_ptr<A> p_4(new A(18));
    A* p_5 = p_4.get();
    // delete p_5; 错误，不能释放，会导致异常，应该有由智能指针管理
    // 同样也不能将别的智能指针绑定到这个返回的裸指针身上，因为释放这个智能指针会导致之前的之智能指针异常
    // {
    //     std::shared_ptr<A> p_6(p_5);
    //     导致异常，因为括号结束了，p_5指向的内存（也就是p_4指向的内存）会被释放
    // }
    // 应该如下使用
    {
        std::shared_ptr<A> p_6(p_4);
    }

    return 0;
}