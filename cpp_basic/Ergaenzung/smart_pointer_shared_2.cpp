#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

class A{
    private:
        int n;
    public:
        A(int _n = 0):n(_n){
            std::cout<<"con called "<<n<<std::endl;
        }
        ~A(){
            std::cout<<"decon called "<<n<<std::endl;
        }
};

void deleter(A* p){
    delete []p;
}

template<class T>
std::shared_ptr<T> make_shared_array(int size_t){
    return std::shared_ptr<T>(new T[size_t], std::default_delete<T[]>());
}

int main(){
    // 9. 指定删除器和数组问题
    // 智能指针绑定数组指针要用自定义删除器，因为默认删除器只会执行delete p，没有[]
    int*p = new int[2];
    *p = 1;
    *(p+1) = 5;
    std::cout<<p[0]<<", "<<p[1]<<std::endl;
    std::shared_ptr<A> p_A(new A[2],std::default_delete<A[]>());        //用智能指针托管数组指针
    std::shared_ptr<A> p_A_1(new A[5],deleter);                         //自己写删除器

    std::cout<<"------------------------------"<<std::endl;
    std::shared_ptr<A> p_arr = make_shared_array<A>(4);
    return 0;
}