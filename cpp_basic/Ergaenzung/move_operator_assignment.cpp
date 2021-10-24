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
            // delete m_pb;             不需要，因为是构造函数，构造的时候还没有指向任何内存
            m_pb = new B(*(tmp.m_pb));
            std::cout<<"A copy con called"<<std::endl;
        }
        A(A&& tmp) noexcept{
            // delete m_pb;             在复制或者移动构造函数中不需要先delete（也就先释放掉内存）
                                        //因为是构造，也就是说新产生的还没指向任何内存，所以不需要这句话 
            m_pb = tmp.m_pb;            //原来对象中tmp.m_pb所指向的内存，现在由m_pb来接管
            tmp.m_pb = nullptr;         //打断原来对象中tmp.m_pb和所指的内存之间的关系，切记！！！
            std::cout<<"A move con called"<<std::endl;
        }
        A& operator=(const A& src){
            std::cout<<"reload operator ="<<std::endl;
            if(this == &src) return *this;
            delete m_pb;                //释放掉自己原来的这块内存
            m_pb = new B(*(src.m_pb));  //重新开辟一块内存,内存上的内容和src中的m_pb指针指向的对象的内容
            return *this;
        }
        A& operator=(A&& src) noexcept{
            std::cout<<"move reload operator ="<<std::endl;
            if(this == &src) return *this;
            delete m_pb;
            m_pb = src.m_pb;            //直接指针赋值，相当于浅拷贝
            src.m_pb = nullptr;         //切断原来对象中m_pb所指向的对象，切记！！！
            return *this;
        }
        ~A(){
            delete m_pb;
            std::cout<<"A decon called"<<std::endl;
        }
};

int main(){
    B* pb = new B();
    pb->m_bm = 19;
    B* pb2 = new B(*(pb));              //这种给参数的new，系统会调用B类的拷贝构造函数
    delete pb;
    delete pb2;
    std::cout<<"----------------------------"<<std::endl;
    A a;
    A a1;
    a1 = a;
    a1 = std::move(a);
    return 0;
}