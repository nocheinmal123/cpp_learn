#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// template class
template <class T1, class T2>
class CPair{
    private:
        T1 key;
        T2 value;
    public:
        CPair(T1 k, T2 v);
        bool operator<(const CPair<T1, T2>& p) const;
        void Print() const;
};
// Pair<T1, T2> is the template class name, should be used as "class name" before

template<class T1, class T2> // member-func also needs the "template" statement
CPair<T1, T2>::CPair(T1 k, T2 v):key(k),value(v){

}

template<class T1, class T2>
bool CPair<T1, T2>::operator<(const CPair<T1,T2>& p) const{
    return key < p.key;
}

template<class T1, class T2>
void CPair<T1, T2>::Print() const{
    std::cout<<key<<", "<<value<<std::endl;
}

int main(){
    std::string name = "yilin";
    CPair<std::string,int> student(name,18);
    student.Print();
    return 0;
}