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
        A(A&& tmp) noexcept{
            m_pb = tmp.m_pb;            //原来对象中tmp.m_pb所指向的内存，现在由m_pb来接管
            tmp.m_pb = nullptr;         //打断原来对象中tmp.m_pb和所指的内存之间的关系，切记！！！
            std::cout<<"A move con called"<<std::endl;
        }
        A& operator=(const A& src){
            std::cout<<"reload operator ="<<std::endl;
            if(this == &src) return *this;
            delete m_pb;                //释放掉自己原来的这块内存
            m_pb = new B(*(src.m_pb));  //重新开辟一块内存,内存上的内容和src中的m_pb指针指向的对象的内容
        }
        A& operator=(A&& src) noexcept{
            std::cout<<"move reload operator ="<<std::endl;
            if(this == &src) return *this;
            delete m_pb;
            m_pb = src.m_pb;            //直接指针赋值，相当于浅拷贝
            src.m_pb = nullptr;         //切断原来对象中m_pb所指向的对象，切记！！！
        }
        ~A(){
            delete m_pb;
            std::cout<<"A decon called"<<std::endl;
        }
};

int main(){
    A a;
    A a1;
    a1 = a;
    a1 = std::move(a);
    return 0;
}