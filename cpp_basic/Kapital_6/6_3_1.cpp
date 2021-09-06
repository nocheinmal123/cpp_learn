#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
class CShape{
    public:
        virtual double getArea() const = 0;
        virtual void PrintInfo() = 0;
        virtual bool operator<(const CShape& c) const = 0;
};

class CRectangle: public CShape{
    public:
        int w,h;
        virtual double getArea() const;
        virtual void PrintInfo();
        virtual bool operator<(const CShape& c) const{
            return this->getArea() < (c).getArea();
        }
};

double CRectangle::getArea() const{
    return w*h;
}

void CRectangle::PrintInfo(){
    std::cout<<"R "<<getArea()<<std::endl;
}

class CCircle: public CShape{
    public:
        int r;
        virtual double getArea() const;
        virtual void PrintInfo();
        virtual bool operator<(const CShape& c) const{
            return this->getArea() > (c).getArea(); // a little different
        }
};

double CCircle::getArea() const{
    return 3.14*r*r;
}

void CCircle::PrintInfo(){
    std::cout<<"C "<<getArea()<<std::endl;
}

class CTriangle: public CShape{
    public:
        int a,b,c;
        virtual double getArea() const;
        virtual void PrintInfo();
        virtual bool operator<(const CShape& c) const{
            return this->getArea() < (c).getArea();
        }
};

double CTriangle::getArea() const{
    double p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

void CTriangle::PrintInfo(){
    std::cout<<"T "<<getArea()<<std::endl;
}

bool cmp(const CShape* c1,const CShape* c2){
    return (c1)->getArea() < (c2)->getArea();
}

int main(){
    // It is very common, when using a array of pointers, which are
    // all pointed to the derived classes. Then when we visit this
    // array, we can do operations of every derived class
    CShape* pShapes[100]; // CShape& pShapes[100] is not allowed
    int n;
    CRectangle* pr;
    CCircle* pc;
    CTriangle* pt;
    std::cin>>n;
    for(int i=0;i<n;i++){
        char c;
        std::cin>>c;
        if(c == 'R'){
            pr = new CRectangle();
            std::cin>>pr->w>>pr->h;
            pShapes[i] = pr;
        }
        else if(c == 'C'){
            pc = new CCircle();
            std::cin>>pc->r;
            pShapes[i] = pc;
        }
        else if(c == 'T'){
            pt = new CTriangle();
            std::cin>>pt->a>>pt->b>>pt->c;
            pShapes[i] = pt;
        }
    }
    std::sort(pShapes,(pShapes+n),cmp);
    for(int i=0;i<n;i++) pShapes[i]->PrintInfo();
    CRectangle cr; cr.w = 10; cr.h = 2;
    CCircle cc; cc.r = 1;
    CTriangle ct; ct.a = 3; ct.b = 4; ct.c = 5;
    std::cout<<(ct<cr)<<std::endl;
    std::cout<<(cc<cr)<<std::endl;
    return 0;
}

/*
T 0
R 42
C 50.24
C 78.5
1
0
*/