#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ostream>
#include <sstream>
// reload of operation of "<<" and ">>"

class Complex{
    private:
        double real,image;
    public:
        Complex(double r,double i);
        ~Complex();
    friend std::ostream & operator <<(std::ostream &out,const Complex &c);
    friend std::istream & operator >>(std::istream &in,Complex &c);
};

Complex::Complex(double r,double i):real(r),image(i){

}

Complex::~Complex(){

}

std::ostream & operator<<(std::ostream &out, const Complex &c){
    out << c.real << "+" << c.image << "i";
    return out;
}

std::istream & operator>>(std::istream &in, Complex &c){
    std::string s;
    in >> s;
    int pos = s.find("+",0);
    std::string stmp = s.substr(0,pos);
    c.real = atof(stmp.c_str());
    stmp = s.substr(pos+1,s.length());
    c.image = atof(stmp.c_str());
    return in;
}

int main(){
    Complex c(1,6);
    int n;
    std::cin >> c >> n;
    std::cout << c <<", "<<n<<std::endl;
    return 0;
}