#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
// normal func, class, member-func of class as the friend of template class

void Func1(){

}

class B{
    public:
        void Func(){

        }
};

class A{

};

template <class T>
class Tmp{               // any obj, which derived from the template class, will own these three friends
    friend void Func1();
    friend class A;
    friend void B::Func();
};

int main(){
    return 0;
}