#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Complex{
    public:
        double real,image;
        void Print(){
            std::cout<<real<<" , "<<image<<std::endl;
        }
        Complex(double real,double image):real(real),image(image){};
        Complex Addone(){
            this->real++;   // <==> real++
            this->image++;  // <==> image++
            this->Print();
            return *this;
        }
};

class A{
    int i;
    public:
    void Hello(){
        std::cout<<"hello"<<std::endl;
        // std::cout<<i<<"hello"<<std::endl;   ----- condition 1
    }
    /*
    actually the complier will do like this:
    void Hello(A *this){
        std::cout<<"hello"<<std::endl;
    }
    the num ofp arameters of static function of class: num of parameters
    the num ofp arameters of non-static function of class: num of parameters + 1(this pointer)
    */
};

int main(){
    Complex c1(1,1),c2(2,3);
    c2 = c1.Addone();

    A *p = NULL;
    p->Hello();
    // p->Hello() is wrong, if conditoin 1 exists
    return 0;
}