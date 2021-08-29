#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ostream>
#include <sstream>
// reload of "type changing", suach double(), or int()...

class Complex{
    private:
        double real,image;
    public:
        Complex(double r = 0,double i = 0);
        operator double(){ // dont need the return value when reloading "type changing"
            return real;
        }
};

Complex::Complex(double r,double i):real(r),image(i){

}

int main(){
    Complex c(1.2, 3.4);
    std::cout<<(double)c<<std::endl; // (double)c <==> c.operator double()
    double n = 2 + c; // <==> double n = 2+ c.operator double()
    // after reloading of "type changing", when compiler read the obj c,
    // it will automatically finish the "type changing" action
    // and return a value, whose type is double
    std::cout << n << std::endl;
    return 0;
}