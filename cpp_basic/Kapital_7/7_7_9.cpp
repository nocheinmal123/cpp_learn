#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// template class and static member-var

template <class T>
class A{
    private:
        static int count; // belongs to different classes
    public:
        A();
        ~A();
        static void Print();
};

template <class T>
A<T>::A(){
    count ++;
}

template <class T>
A<T>::~A(){
    count --;
}

template <class T>
void A<T>::Print(){
    std::cout<<"count = "<<count<<std::endl;
}

template<> int A<int>::count = 0;
template<> int A<double>::count = 0;

int main(){
    A<int> a1;
    A<double> a3;
    a1.Print();
    A<int> a2;
    a2.Print();
    a3.Print();
    return 0;
}
/*
1
2
1
*/