#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// template class as friend of template class

template <class T>
class B{
    T v;
    public:
        B(T n);
        template <class T1>
        friend class A;
};

template <class T>
B<T>::B(T n):v(n){

}

template<class T>
class A{
    public:
        void Func(){
            B<int> o(10);
            std::cout<<o.v<<std::endl;
        }
};

int main(){
    A<double> a;
    a.Func();
    return 0;
}