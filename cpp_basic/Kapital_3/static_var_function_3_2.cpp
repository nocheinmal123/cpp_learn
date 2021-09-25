#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class CReactangle{
    private:
        int w,h;
        // static class members, is actually the global vars !!
        static int TotalArea; 
        static int Totalnum;
    public:
        CReactangle(int w_,int h_);
        ~CReactangle();
        // static function, won't work at some objs, just work at class
        // is actually global functions !! 
        // in static functions, can not visit non-static vars or non-static funtions
        static void Print();
};

CReactangle::CReactangle(int w_,int h_){
    w = w_;
    h = h_;
    TotalArea += w_ * h_;
    Totalnum += 1;
}

CReactangle::~CReactangle(){
    TotalArea -= w * h;
    Totalnum --;
}

void CReactangle::Print(){ // dont add static here
    printf("TotalArea = %d, Totalnum = %d\n",TotalArea,Totalnum);
}

// even if the vars are "private", we must still define them like this,
// plus, the static var must be initialized like global vars
int CReactangle::TotalArea = 0;
int CReactangle::Totalnum = 0;

class Myclass{
    int n;
    static int s;
};

int main(){
    CReactangle r1(3,5);
    r1.Print();
    CReactangle r2 = r1;
    r2.Print();
    CReactangle r3(r2);
    r3.Print();
    // the three above use copy constructor, so if we dont code copy constructor
    // ourself, static vars will not change
    CReactangle *p = new CReactangle(3,7);
    p->Print();
    delete p;
    CReactangle r4(4,5);
    r4.Print();

    // "sizeof" won't calculate the static var of class, cauz static vars are global
    printf("%ld\n",sizeof(Myclass));
    return 0;
}

/*
TotalArea = 15, Totalnum = 1
TotalArea = 15, Totalnum = 1
TotalArea = 15, Totalnum = 1
TotalArea = 36, Totalnum = 2
TotalArea = 35, Totalnum = 2
4
*/