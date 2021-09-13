#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Shape{
    protected:
        int width;
        int height;
    public:
        Shape(int w = 0,int h = 0);
        ~Shape();
        virtual int getArea() const;
        virtual void Print() const;
};

Shape::Shape(int w, int h):width(w),height(h){

}

Shape::~Shape(){

}

int Shape::getArea() const{
    return width*height;
}

void Shape::Print() const{
    std::cout<<"Shape"<<std::endl;
    std::cout<<width<<", "<<height<<std::endl;
}

class Rectangle: public Shape{
    public:
        Rectangle(int w,int h);
        ~Rectangle();
        virtual int getArea() const;
        virtual void Print() const;
};

Rectangle::Rectangle(int w,int h):Shape(w,h){

}

Rectangle::~Rectangle(){

}

int Rectangle::getArea() const{
    return width*height;
}

void Rectangle::Print() const{
    std::cout<<"Rec"<<std::endl;
    std::cout<<width<<", "<<height<<std::endl;
}

class Triangle: public Shape{
    public:
        Triangle(int w,int h);
        ~Triangle();
        virtual int getArea() const;
        virtual void Print() const;
};

Triangle::Triangle(int w,int h):Shape(w,h){

}

Triangle::~Triangle(){

}

int Triangle::getArea() const{
    return width*height/2;
}

void Triangle::Print() const{
    std::cout<<"Tri"<<std::endl;
    std::cout<<width<<", "<<height<<std::endl;
}

int main(){

    Shape* p;
    Shape sh;
    Rectangle rec(10,7);
    Triangle tri(8,6);
 
    p = &rec;
    // std::cout<<p->getArea()<<std::endl;
    // p->Print();

    p = &tri;
    // std::cout<<p->getArea()<<std::endl;
    // p->Print();

    std::cout<<"-----------------"<<std::endl;
    *p = Rectangle(20,10);
    std::cout<<p->getArea()<<std::endl;
    p->Print();

    *p = Triangle(4,4);
    std::cout<<p->getArea()<<std::endl;
    p->Print();
    return 0;
}
/*
-----------------
100
Tri
20, 10
8
Tri
4, 4
If the Compiler find that, p is a pointer, whose type is class X, it will
use it to visit the member of of class X (if polymorphsim is used, the compiler
will find the class Y, which is pointed by pointer p).
*/