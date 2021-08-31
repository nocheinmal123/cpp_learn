#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class Complex{
    public:
        double real,image;
    Complex(double r = 0, double i = 0):real(r),image(i){};
    Complex operator-(const Complex &c); // reload operation -, as a member func of class,
    // the num of parameters is 2 - 1 = 1
    bool operator < (const Complex &c);
};

// reload operation +, as a normal function, the num of parameters is the num
// of the num of operaion +, is just 2
Complex operator+(const Complex &a,const Complex &b){
    return Complex(a.real + b.real, a.image + b.image);
}

Complex Complex::operator-(const Complex &c){
    // return Complex(c.real - this->real, c.image - this->image);
    return Complex(this->real - c.real, this->image - c.image);
}

bool Complex::operator<(const Complex &c){
    if(this->real == c.real) return this->image < c.image;
    return this->real < c.real;
}

int main(){
    Complex a(4,4),b(1,1),c;
    c = a + b;  // <==>  c=operator+(a,b)
    std::cout<<c.real<<", "<<c.image<<std::endl;
    std::cout<<(a-b).real<<", "<<(a-b).image<<std::endl;
    // a-b <==> a.operator-(b)
    if (a<b) printf("a < b\n");
    else printf("a >= b\n");
    return 0;
}