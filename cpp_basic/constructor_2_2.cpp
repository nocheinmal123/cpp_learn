#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Complex{
    private:
        double real,image;
    public:
        Complex(double r,double i = 0);
        Complex(Complex c1,Complex c2);
};

Complex::Complex(double r,double i){
    real = r;
    image = i;
}

Complex::Complex(Complex c1,Complex c2){
    real = c1.real + c2.real;
    image = c1.image + c2.image;
}

// constructor in array of object
class CSample{
    int x;
    public:
        CSample(){
            std::cout<<"Constructor 1 called"<<std::endl;
        }
        CSample(int n){
            x = n;
            std::cout<<"Constructor 2 called"<<std::endl;
        }
};

class Test{
    public:
        Test(int n){}
        Test(int n,int m){}
        Test(){}
};

int main(){
    Complex c1(2);
    Complex c2(4,5);
    Complex c3(c1,c2);

    std::cout<<"step 1"<<std::endl;
    CSample arr1[2]; // 1 and 1 Called
    std::cout<<"step 2"<<std::endl;
    CSample arr2[2] = {4,5}; // 2 and 2 Called
    std::cout<<"step 3"<<std::endl;
    CSample arr3[2] = {3}; // 2 and 1 Called
    std::cout<<"step 4"<<std::endl;
    CSample *arr4 = new CSample[2]; // 1 and 1 Called
    delete []arr4;

    Test arr_test[3] = {1,Test(1,2)}; // using the first, second and third constructor
    Test arr_test2[3] = {Test(1,2),Test(4,5),1}; // using the second, second, first constructor
    Test *parr[3] = {new Test(4),new Test(1,2)}; // using the first, second, but the third was not created
    // parr[2] is just an empty pointer without initialization

    return 0;
}