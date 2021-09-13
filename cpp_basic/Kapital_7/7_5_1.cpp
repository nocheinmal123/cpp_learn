#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// function template and class template

/*
void swap(int& x,int & y){
    int temp = x;
    x = y;
    y = temp;
}

void swap(double& x,double& y){
    double temp = x;
    x = y;
    y = temp;
}
*/

template <class T>
void swap(T& x,T& y){
    T temp = x;
    x = y;
    y = temp;
}

template <class T1, class T2>
T2 Print(T1 arg1, T2 arg2){
    std::cout<<arg1<<" "<<arg2<<std::endl;
    return arg2;
}

template <class T>
T MaxElement(T a[], int size){
    T tmpMax = a[0];
    for(int i=0;i<size;i++){
        if(tmpMax < a[i]) tmpMax = a[i];
    }
    return tmpMax;
}

template <class T>
T Inc(T n){
    return 1 + n;
}

// reload the template of the function
// if the parameter of func are different or the <class T1, class Tx...> are different

// template<class T1, class T2>    // already declared at line 30
// void Print(T1 arg1, T2 arg2){
//     std::cout<<"1"<<std::endl;
//     std::cout<<arg1<<", "<<arg2<<std::endl;
// }

template<class T>
void Print(T arg1, T arg2){
    std::cout<<"2"<<std::endl;
    std::cout<<arg1<<", "<<arg2<<std::endl;
}

template<class T, class T2>
void Print(T arg1, T arg2){
    std::cout<<"3"<<std::endl;
    std::cout<<arg1<<", "<<arg2<<std::endl;
}

int main(){
    int n = 1; int m = 2;
    swap(n,m);
    std::cout<<n<<", "<<m<<std::endl;
    double f = 1.2, g = 3.4;
    swap(f,g);
    std::cout<<f<<", "<<g<<std::endl;

    int s[10];
    for(int i = 0;i<10;i++) s[i] = i + 12;
    std::cout<<MaxElement(s,10)<<std::endl;

    std::cout<<Inc<double>(4)/2<<std::endl; // "realize" the template function without using parameters

    Print(2,3);
    Print(1.2,3);
    return 0;
}

/*
The sequence of the template-func and func 
1. Firstly the normal func, whose parameters and type can totally match
2. Then the template func, whose parameters can totally match
3. Then the normal func, whose parameters will be transferred automatically
4. If all funcs above can't be found, then error
*/