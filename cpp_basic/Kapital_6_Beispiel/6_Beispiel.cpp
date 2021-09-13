#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>

class Shape{
    protected:
        int width;
        int height;
    public:
        Shape(int w = 0, int h = 0);
        ~Shape();
        virtual int getArea() const;
        virtual void Info() const{
            std::cout<<"Shape Info: "<<width<<", "<<height<<std::endl;
        }
        virtual void Print() const;
};

Shape::Shape(int w,int h):width(w),height(h){
    // std::cout<<"shape con"<<std::endl;
}

Shape::~Shape(){
    // std::cout<<"Shape decon"<<std::endl;
}

int Shape::getArea() const{
    return width*height;
}

void Shape::Print() const{
    std::cout<<"Shape Area = "<<getArea()<<std::endl;
}

class Rectangle: public Shape{
    public:
        Rectangle(int w = 0,int h = 0);
        ~Rectangle();
        virtual int getArea() const;
        virtual void Info() const{
            std::cout<<"Rec Info: "<<width<<", "<<height<<std::endl;
        }
        virtual void Print() const;
};

Rectangle::Rectangle(int w,int h):Shape(w,h){
    // std::cout<<"Rec con"<<std::endl;
}

Rectangle::~Rectangle(){
    // std::cout<<"Rec decon"<<std::endl;
}

int Rectangle::getArea() const{
    return width*height;
}

void Rectangle::Print() const{
    std::cout<<"Rec Area = "<<getArea()<<std::endl;
}

class Triangle: public Shape{
    public:
        Triangle(int w = 0, int h = 0);
        ~Triangle();
        virtual int getArea() const;
        virtual void Info() const{
            std::cout<<"Tri Info: "<<width<<", "<<height<<std::endl;
        }
        virtual void Print() const;
};

Triangle::Triangle(int w,int h):Shape(w,h){
    // std::cout<<"Tri con"<<std::endl;
}

Triangle::~Triangle(){
    // std::cout<<"Tri decon"<<std::endl;
}

int Triangle::getArea() const{
    return width*height/2;
}

void Triangle::Print() const{
    std::cout<<"Tri Area = "<<getArea()<<std::endl;
}

int main(){
    Shape* p;
    Rectangle rec(10,3);
    Triangle tri(5,4);
    p = &rec;
    (*p).Print();
    *p = tri; // just change the value of the member-var, won't change the type of the pointed obj (still class rec)
    // so, the call of virtual member-fun is still the func of class rec, still using the member-var of calss func
    // but the value of member-var changed
    (*p).Print();
    (*p).Info();
    return 0;
}