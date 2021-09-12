#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ostream>
#include <sstream>

class Complex{
    private:
        double real,image;
    public:
        Complex(double r = 0,double i = 0);
        ~Complex();
    friend std::ostream& operator <<(std::ostream& out, const Complex& c);
    friend std::istream& operator >>(std::istream& in, Complex& c);
};

Complex::Complex(double r,double i):real(r),image(i){
    std::cout<<"con called"<<std::endl;
}

Complex::~Complex(){
    std::cout<<"decon called"<<std::endl;
}

std::ostream& operator<<(std::ostream& out, const Complex& c){
    out<<c.real<<"+"<<c.image<<"i";
    return out;
}

std::istream& operator>>(std::istream& in, Complex& c){
    std::string s;
    in >> s;
    int pos = s.find("+",0);
    std::string stemp = s.substr(0,pos);
    c.real = atof(stemp.c_str());
    stemp = s.substr(pos+1,s.length());
    c.image = atof(stemp.c_str());
    return in;
}


int main(){
    Complex c(2.1,7.8);
    int n;
    std::cin>>c>>n;
    std::cout<<c<<std::endl;
    std::cout<<n<<std::endl;
    return 0;
}