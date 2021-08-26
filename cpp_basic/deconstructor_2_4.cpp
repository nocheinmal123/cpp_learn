#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Complex{
    public:
        double real,image;
        Complex(int i){
            std::cout<<"Intconstructor called"<<std::endl;
            real = i;
            image = 0;
        }
        Complex(double r,double i){
            std::cout<<"Constructor called"<<std::endl;
            real = r;
            image = i;
        }
};

class Testclass{
    public:
        int n;
        explicit Testclass(int par){ //with "explicti", constructor must ask one
        // parameter while initialization
            n = par;
        }
};

class String{
    private:
        char *p;
    public:
        String(){
            p = new char[10];
        }
        ~String();
};

String::~String(){
    delete []p;
}

class Ctest{
    public:
        explicit Ctest(){
            std::cout<<"constructor called"<<std::endl;
        }
        ~Ctest(){
            std::cout<<"destructor called"<<std::endl;
        }
};

int main(){
    Complex c1(7,8);
    Complex c2 = 12; // here 12 will be automatically transferred into a temp obj
    c1 = 9;          // 9 will be automatically tranferred into a temp obj
    std::cout<<c1.real<<","<<c1.image<<std::endl;
    Testclass cl(10);
    // Testclass c1 = 10; wrong, cauz "explicit"

    Ctest arr[2];
    std::cout<<"End Main"<<std::endl;
    /*
    if only have above code, the output should be:
        End Main
        destructor called
        destructor called
    */

    // delete calls deconstructor
    Ctest *pTest;
    pTest = new Ctest; // constructor called
    delete pTest;      // deconstructor called
    pTest = new Ctest[3]; // constructor called 3 times
    delete []pTest;       // deconstructor called 3 times
    return 0;
}