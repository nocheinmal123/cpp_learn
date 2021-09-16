#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <iostream>
// keyword "auto"

std::map<std::string,int> Map;
class A{
    private:
        int v;
        // int v = 89; since C++ 11, the memer-var can have a default value when initialization
    public:
        A(int _v);
        void Print();
        template <class T>
        friend A operator+(const T x,const A& y);
};

A::A(int _v):v(_v){

}

void A::Print(){
    std::cout<<"v = "<<v<<std::endl;
}

template <class T>
A operator+(const T x,const A& y){
    return A(x + y.v);
}

template <class T1, class T2>
auto Add(T1 x,T2& y){
    std::cout<<typeid(x).name()<<std::endl;
    std::cout<<typeid(y).name()<<std::endl;
    return x + y;
}

template <class T1, class T2>
auto add(T1 x,T2& y){
    return x + y;
}

int main(){
    A a(10);
    A c(12);
    double b = 3.2;
    double t = 7.6;;
    auto ans1 = Add(b,c); std::cout<<typeid(ans1).name()<<std::endl;
    ans1.Print();
    auto ans2 = add(b,a);
    ans2.Print();
    auto ans3 = add(b,t); std::cout<<ans3<<std::endl; std::cout<<typeid(ans3).name()<<std::endl;

    // std::map<std::string,int>::iterator i = Map.begin(); can now be replaced by "auto"
    for(auto i = Map.begin();i!=Map.end();i++);
    return 0;
}