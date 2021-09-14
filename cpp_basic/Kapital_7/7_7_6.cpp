#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// template func as friend as template class

template <class T1, class T2>
class Pair{
    private:
        T1 key;
        T2 value;
    public:
        Pair<T1, T2>(T1 k,T2 v);
        ~Pair<T1, T2>();
        bool operator<(const Pair<T1, T2>& p) const;
        template<class T3, class T4>
        friend std::ostream& operator<<(std::ostream& out, const Pair<T3,T4>& p);
};

template <class T1, class T2>
Pair<T1,T2>::Pair(T1 k ,T2 v):key(k),value(v){

}

template <class T1, class T2>
Pair<T1,T2>::~Pair(){

}

template <class T1, class T2>
bool Pair<T1,T2>::operator<(const Pair<T1,T2>& p) const{
    if(key == p.key) return value < p.value;
    return key < p.key;
}

template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const Pair<T1,T2>& p){
    out<<"("<<p.key<<", "<<p.value<<")";
    return out;
}

int main(){
    Pair<int,int> obj1(10,2);
    Pair<int,int> obj4(7,6);
    Pair<double,int> obj2(7,10);
    Pair<double,double> obj3(12.3,8);
    std::cout<<obj1<<std::endl;
    std::cout<<obj2<<std::endl;
    std::cout<<obj3<<std::endl;
    std::cout<<(obj1 < obj4)<<std::endl;

    Pair<std::string,int> obj("yilin",20);
    std::cout<<obj<<std::endl;
    return 0;
}
/*
(10, 2)
(7, 10)
(12.3, 8)
0
(yilin, 20)
*/