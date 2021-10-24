#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

class B{
    public:
        int m_bm;
        B():m_bm(100){
            // std::cout<<"B con called"<<std::endl;
        }
        B(const B& tmp){
            this->m_bm = tmp.m_bm;
            // std::cout<<"B copy con calld"<<std::endl;
        }
        virtual ~B(){
            // std::cout<<"B decon called"<<std::endl;
        }
};

class A{
    private:
        B* m_pb;
    public:
        A():m_pb(new B()){
            std::cout<<"A con called"<<std::endl;
        }
        A(const A& tmp){
            m_pb = new B(*(tmp.m_pb));
            std::cout<<"A copy con called"<<std::endl;
        }
        A(A&& tmp){
            m_pb = tmp.m_pb;            //原来对象中tmp.m_pb所指向的内存，现在由m_pb来接管
            tmp.m_pb = nullptr;         //打断原来对象中tmp.m_pb和所指的内存之间的关系
            std::cout<<"A move con called"<<std::endl;
        }
        ~A(){
            delete m_pb;
            std::cout<<"A decon called"<<std::endl;
        }
};

A getA(){
    A a;
    return a;
}

int main(){
    B b1;
    B b2(b1);
    B* pb = new B();
    pb->m_bm = 19;
    B* pb2 = new B(*pb); //这种给参数的new，系统会调用B类的拷贝构造函数
    std::cout<<"Adress of pb is "<<pb<<std::endl;
    std::cout<<"Adress of pb2 is "<<pb2<<std::endl;
    delete pb;
    delete pb2;

    A a = getA(); //在这里，原本会发生两次A的拷贝构造函数发生，一次是return a,一次是这里的赋值
    // 但是，由于A中有移动构造函数的存在，将不再调用拷贝构造函数，取而代之的是两次移动构造函数调用
    // 编译器是智能的，他知道这时候调用移动构造函数更合适
    A a1(a);                //调用拷贝构造函数
    A a2(std::move(a));     //调用移动构造函数
    A&& ref = getA();       //更好的做法，因为可以避免移动构造函数/拷贝构造函数的调用
    //现在getA()返回的临时对象的生命周期和ref是一样的了
    return 0;
}