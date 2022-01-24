#include "11_7_complex.h"

namespace COMPLEX{
    Complex::Complex(int _r, int _i){
        this->real = _r;
        this->image = _i;
    }
    Complex::~Complex(){

    }
    Complex::Complex(const Complex& src){
        this->real = src.real;
        this->image = src.image;
    }
    Complex::Complex(Complex&& src){
        this->real = src.real;
        this->image = src.image;
    }
    Complex Complex::operator+(const Complex& src){
        return Complex(this->real + src.real, this->image + src.image);
    }
    Complex Complex::operator-(const Complex& src){
        return Complex(this->real - src.real, this->image - src.image);
    }
    Complex Complex::operator*(const Complex& src){
        return Complex(this->real * src.real, this->image * src.image);
    }
    Complex Complex::operator*(int mult){
        return Complex(mult * this->real, mult * this->image);
    }
    Complex& Complex::operator~(){
        this->image = -this->image;
        return *this;
    }
    std::ostream& operator<<(std::ostream& out, const Complex& src){
        out << "r = " << src.real << ", i = " << src.image;
        return out;
    }
    std::istream& operator>>(std::istream& in, Complex& src){
        in >> src.real >> src.image;
        return in;
    }
}