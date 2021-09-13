#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>

class Complex{
    private:
        double real,image;
    public:
        Complex(double r = 0,double i = 0):real(r),image(i){

        }
        ~Complex(){

        }
        bool operator<(const Complex& c){
            if(this->real == c.real) return this->image < c.image;
            else return this->real < c.real;
        }
        Complex(const Complex& c){
            this->real = c.real;
            this->image = c.image;
        }
        void Print(){
            std::cout<<real<<", "<<image<<std::endl;
        }
};

template <class T>
T Max(T a, T b){
    std::cout<<"TemplateMax"<<std::endl;
    if(a < b) return b;
    else return a;
}

template <class T,class T2>
T Max(T a, T2 b){
    std::cout<<"TemplateMax2"<<std::endl;
    if(a < b) return b;
    else return a;
}

double Max(double a,double b){
    std::cout<<"Max"<<std::endl;
    return std::max(a,b);
}


int main(){
    Complex c1(10,1.2);
    Complex c2(12,1); 
    Max(c1,c2).Print();

    int i = 4, j = 5;
    Max(1.2, 3.4); // Max
    Max(i, j); // TemplateMax
    Max(1.2, 3); // TemplateMax2
    return 0;
}
// When matching template function, the compiler won't do type-automatical-changing !!