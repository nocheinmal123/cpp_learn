#include <iostream>
#include <string>
#include <string.h>

namespace COMPLEX{
    class Complex{
        private:
            int real;
            int image;
        public:
            explicit Complex(int _r = 0, int _i = 0);
            Complex(const Complex& src);
            Complex(Complex&& src);
            ~Complex();
            Complex operator+(const Complex& src);
            Complex operator-(const Complex& src);
            Complex operator*(int mult);
            Complex operator*(const Complex& src);
            Complex& operator~();
            friend std::istream& operator>>(std::istream& in, Complex& src);
            friend std::ostream& operator<<(std::ostream& out, const Complex& src);
    };
}