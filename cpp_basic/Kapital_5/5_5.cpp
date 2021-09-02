#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class base{

};

class derived: public base{

};

int main(){
    base b;
    derived d;
    b = d; // 1. derived class can assign to base class
    // d = b; wrong, base class cannot assign to derived class
    base &br = d; // 2. the ref of a base class can ref to derived class
    base *pb = &d; // 3. the pointer of a base class can be pointed to a derived class
    return 0;
}