#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
reload operation as friend function
Normally, we reload the operation function as member-func of class,
but sometimes, it doesn't meet the needs. We have to reload this operation function
as global function, but the global function can't visit the private vars of class
so we reload the operation function as friend function of class
*/

class Complex{
    double real,image;
    public:
        Complex(double r,double i);
        Complex operator+(double r);
        Complex& operator=(const Complex& c);
        void Print(){
            std::cout<<real<<", "<<image<<std::endl;
        }
        friend Complex operator+(double r, const Complex &c);
};

Complex::Complex(double r,double i):real(r),image(i){

}

Complex Complex::operator+(double r){
    std::cout<<"reload 1"<<std::endl;
    return Complex(this->real + r,this->image);
}
// Complex c(10,2);
// using the above reload, c = c + 5 can work now, <==> c = c.operator+(5)
// but c = 5 + c still doesn't work

Complex operator+(double r,const Complex &c){
    std::cout<<"reload 2"<<std::endl;
    return Complex(r + c.real, c.image);
}

Complex& Complex::operator=(const Complex& c){
    std::cout<<"reload ="<<std::endl;
    real = c.real;
    image = c.image;
    return *this;
}

int main(){
    Complex c(10,2);
    c.Print();
    c = c + 5;
    c.Print();
    c = 10 + c;
    c.Print();
    return 0;
}
/*
Output:
10, 2
reload 1
15, 2
reload 2
25, 2
*/