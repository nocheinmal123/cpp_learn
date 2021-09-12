#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ostream>
#include <sstream>
// reload of operation "++" and "--"
class CDemo{
    private:
        int n;
    public:
        explicit CDemo(int x);
        ~CDemo();
        CDemo(const CDemo &c);
        CDemo & operator++();   // using for "++a"
        CDemo operator++(int);  // using for "a++", need one more "int" in the parameters of func
    friend CDemo & operator--(CDemo &c);
    friend CDemo operator--(CDemo &c,int);
    friend std::ostream & operator<<(std::ostream &out,const CDemo &c);
};

CDemo::CDemo(int x):n(x){
    std::cout<<"con called"<<std::endl;
}

CDemo::CDemo(const CDemo &c){
    std::cout<<"copy con called"<<std::endl;
    n = c.n;
}

CDemo & CDemo::operator++(){
    // ++a, in C++, original return value of "++a" is the ref of a
    ++ n;
    return *this;
    // ++a <==> a.operator++()
}

CDemo CDemo::operator++(int){
    // a++, in C++, original return value of "a++" is just a
    CDemo temp(*this);
    n ++;
    return temp;
    // a++ <==> a.operator++(0);
}

CDemo & operator--(CDemo &c){
    // --a
    c.n --;
    return c;
    // --a <==> a.operator--(class)
}

CDemo operator--(CDemo &c,int ){
    // a--
    CDemo temp(c);
    c.n --;
    return temp;
    // a-- <==> a.operator--(class,0)
}

CDemo::~CDemo(){

}

std::ostream & operator<<(std::ostream &out,const CDemo &c){
    out<<c.n;
    return out;
}

int main(){
    CDemo d(5);
    std::cout << d++<<std::endl;   // <==> d.operator++(0); member-func
    std::cout << d<<std::endl;     //
    std::cout << ++d<<std::endl;   // <==> d.operator++(); member func

    std::cout << d--<<std::endl;   // <==> operator--(d,0); friend func
    std::cout << d<<std::endl;     //
    std::cout << --d<<std::endl;   // <==> operator--(d); friend func
    CDemo e(d);
    return 0;
}