#include "11_7_complex.h"

int main(){
    using namespace COMPLEX;
    Complex a(3, 4);
    Complex c;
    std::cout << "Enter a complex number (q to quit):\n";
    while(std::cin >> c){
        std::cout << "c is " << c << '\n';
        std::cout << "a is " << a << '\n';
        std::cout << a + c << std::endl;
        std::cout << a - c << std::endl;
        std::cout << a * c << std::endl;
        std::cout << c * 2 << std::endl;
        std::cout << ~c << std::endl;
    }
    return 0;
}