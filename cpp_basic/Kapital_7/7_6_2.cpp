#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// template function as the member-func of a template class

template <class T>
class A{
    public:
        template<class T2>
        void Func(T2 t){
            std::cout<<t<<std::endl;
        }
};

template<class T, int size> // there can be non-class type in the template class
class CArray{
    T array;
    public:
        template<class T1>
        CArray(T1 s):array(s){

        }
        void Print(){
            for(int i=0;i<size;i++) std::cout<<array[i]<<" ";
            std::cout<<std::endl;
        }
};


int main(){
    A<int> a;
    a.Func("K"); // template member-func is been "obj-realized"
    a.Func(34); // template member-func is been "obj-realized" again
    a.Func('l');
    double b[5] = {1.1, 2.3, 4.2, 10, 5.3};
    CArray<double*,5> arr(b);
    arr.Print();

    CArray<double*,5>* p = &arr;
    p->Print();
    return 0;
}