#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class A{

};

int main(){
    A *p = new A[2];
    A *p2 = new A;
    A a;
    delete []p;
    return 0;
}

/*
how many times does decon will be called? 3times
Cauz the things, which are declared with "new", must use "delete", so the decon will
be called.
A *p2 = new A;
this p2 will not call decon while main ends
*/