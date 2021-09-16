#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
// static_cast, interpret_cast, const_cast, dynamic_cast
class A{
    public:
        operator int(){
            return 1;
        }
        operator char*(){
            return NULL;
        }
};


int main(){
    A a;
    char x[] = "New INn";
    int n;
    char* p = x;
    n = static_cast<int>(3.14); // n becomes 3
    std::cout<<n<<std::endl;
    n = static_cast<int>(a); // a.operator int calleed, n becomes 1
    std::cout<<n<<std::endl;

    p = static_cast<char*>(a); std::cout<<p<<std::endl; // pa.operator char* is called, p becomes NULL
    // n = static_cast<int>(p); wrong, static_cast can only have basic function, can't
    // change typem from pointer to int
    // p = static_cast<char*>(n); also wrong
    return 0;
}