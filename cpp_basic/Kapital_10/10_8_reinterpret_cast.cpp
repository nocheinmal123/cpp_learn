#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
// reinterpret_cast
// used to transfer among the different kinds of pointer, different kinds of refereces
// pointer and int (the size of int must be the same as the size of pointer, all 4 bytes)

class A{
    public:
        int i;
        int j;
        A(int n):i(n),j(n){

        }
};


int main(){
    A a(100);
    int& r = reinterpret_cast<int&>(a); //let r ref to obj a
    r = 200;
    std::cout<<a.i<<", "<<a.j<<std::endl; // 200, 100
    int n = 300;
    A* pa = reinterpret_cast<A*>(&n); // left pa points to n
    pa->i = 400; // n becomes 400
    std::cout<<n<<std::endl;
    pa->j = 500; // not safe, maybe core dump
    long long la = 0x12345678abcdLL;
    pa = reinterpret_cast<A*>(la); // la is too long, only low-32-bit will be copied to pa
    // which is 0x5678abcd
    unsigned int u = reinterpret_cast<unsigned int>(pa);
    std::cout<<std::hex<<u<<std::endl;
    return 0;
}