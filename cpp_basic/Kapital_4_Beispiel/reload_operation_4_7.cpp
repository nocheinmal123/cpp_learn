#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ostream>
#include <sstream>
// practice of reload operator "a++" and "++a"
// "++a" needs a return value, whose type is ref
// "a++" needs just a normal value type, but one more "int" in parameter of
// reload-func

class Complex{
    private:
        double real,image;
    public:
        Complex(double r,double i);
        ~Complex();
        Complex(const Complex& c);
        Complex& operator++();
        Complex operator++(int);
    friend Complex& operator--(Complex& c);
    friend Complex operator--(Complex& c,int);
    friend std::ostream& operator<<(std::ostream& out,const Complex& c);
};

Complex::Complex(double r,double i):real(r),image(i){
    std::cout<<"con called"<<std::endl;
}

Complex::~Complex(){
    std::cout<<"decon called"<<std::endl;
}

Complex::Complex(const Complex& c){
    std::cout<<"copy con called"<<std::endl;
    real = c.real;
    image = c.image;
}

Complex& Complex::operator++(){
    real += 1;
    image += 1;
    return *this;
}

Complex Complex::operator++(int){
    Complex c = *this;
    real += 1;
    image += 1;
    return c;
}

Complex& operator--(Complex& c){
    c.real -= 1;
    c.image -= 1;
    return c;
}

Complex operator--(Complex& c,int){
    Complex _c = c;
    c.real -= 1;
    c.image -= 1;
    return _c;
}

std::ostream& operator<<(std::ostream& out,const Complex& c){
    out<<c.real<<"+"<<c.image<<"i";
    return out;
}

int main(){
    Complex c1(9,6.7);
    std::cout<<c1<<std::endl;
    ++c1;
    std::cout<<c1<<std::endl;
    std::cout<<c1++<<std::endl;
    std::cout<<c1<<std::endl;

}