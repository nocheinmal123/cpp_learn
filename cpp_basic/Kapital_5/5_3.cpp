#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class base{
    private:
        int j;
    public:
        int i;
        void func();
};

void base::func(){
    std::cout<<"base func"<<std::endl;
}

class derived:public base{
    public:
        int i; // Deckung of the same member in father class
        void access();
        void func(); // Deckung of the same func in father class
};

void derived::access(){
    std::cout<<"derived access"<<std::endl;
    // j = 5; wrong, the private member var or func cant be visited by son class
    i = 5; // son class
    base::i = 10; // father class
    func(); // son class
    base::func(); // father class
}

void derived::func(){
    std::cout<<"derived func"<<std::endl;
}


/*******protected*********/
class Father{
    private:
        int nPrivate;
    public:
        int nPublic;
    protected:
        int nProtected;
};

class Son: public Father{
    void AccessFather(){
        nPublic = 1;
        // nPrivate = 1; wrong
        nProtected = 1;
        Son f;
        // f.nProtected = 1; wrong, f is not "presenting obj"
        // "presenting obj" means the obj, which now is worked by the member function
    }
};

int main(){
    derived obj;
    obj.access();
    obj.i = 1; // son class
    obj.func();
    obj.base::i = 10; // father class
    obj.base::func();

    Father f;
    Son s;
    f.nPublic = 1;
    s.nPublic = 2;
    // f.nProtected = 1; wrong, can be visited member-func of father class, friend member-func of father class
    // and the "presenting obj" of the member-func of derived class
    // s.nProtected = 2; wrong

    // f.nPrivate = 1; wrong
    // s.nPrivate = 2; wrong

    return 0;
}