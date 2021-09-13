#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// virtual func and polymorphism

// virtual func

class Base{
    virtual int get();
};

int Base::get(){
    // dont write "virtual", "virtual" only at the declaration of the virtual-fun
}

// The pointer of derived class can be assigned to base class
/*
base = derived
so, when we use this pointer, which is pointed to base class, to call
the func both in base class and derived class, we know
1. If this pointer points to a obj of base class, it will call
    the func of base class
2. If this pointer points to a obj of derived class, it will call 
    the func of derived class

It is called polymorphism
*/

class Shape{
    protected:
        int width,height;
    public:
        Shape(int w = 0,int h = 0){
            width = w;
            height = h;
        }
        void Print(){
            std::cout<<"w = "<<width<<"  "<<"h = "<<height<<std::endl;
        }
        virtual int getArea(){
            std::cout<<"Shape"<<std::endl;
            return width * height;
        }
};

class Rectangle: public Shape{
    public:
        Rectangle(int w = 0,int h = 0):Shape(w,h){}
        int getArea(){
            std::cout<<"Rec"<<std::endl;
            return width * height;
        }
};

class Triangle: public Shape{
    public:
        Triangle(int w = 0,int h = 0):Shape(w,h){}
        int getArea(){
            std::cout<<"Tri"<<std::endl;
            return width * height / 2;
        }
};

int main(){
    Shape *ps;
    Rectangle rec(10,7);
    Triangle tri(8,6);

    /*
    if no "virual" in the base class
    ps = &rec;
    std::cout<<ps->getArea()<<std::endl;
    ps = &tri;
    std::cout<<ps->getArea()<<std::endl;

    The Output is :
    Shape
    70
    Shape
    48
    */
    // so we have to put "virtual" in front of the func in base class
    /*
    And now, the Output is:
    Rec
    70
    Tri
    24
    */

    ps = &rec;
    std::cout<<ps->getArea()<<std::endl;
    ps = &tri;
    std::cout<<ps->getArea()<<std::endl;

    
    // Shape &ref = rec;
    // std::cout<<ref.getArea()<<std::endl;
    Shape &ref = tri;
    std::cout<<ref.getArea()<<std::endl;

    /*
    Rec
    70
    and the "not commented" is:
    Tri
    24
    cant at same time, cauz the ref cant be defined twice, once it is defined, it will not change
    */
    std::cout<<rec.Shape::getArea()<<std::endl;
    std::cout<<rec.getArea()<<std::endl;
    std::cout<<tri.Shape::getArea()<<std::endl;
    std::cout<<tri.getArea()<<std::endl;
    /*
    Output:
    Shape
    70
    Rec
    70
    Shape
    48
    Tri
    24
    */
    return 0;
}