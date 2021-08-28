#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class CReactangle{
    private:
        int w,h;
        // static class members
        static int TotalArea; 
        static int Totalnum;
    public:
        CReactangle(int w_,int h_);
        CReactangle(const CReactangle &x);
        ~CReactangle();
        // static function
        static void Print();
};

CReactangle::CReactangle(int w_,int h_){
    w = w_;
    h = h_;
    TotalArea += w_ * h_;
    Totalnum += 1;
}

CReactangle::CReactangle(const CReactangle &x){
    w = x.w;
    h = x.h;
    TotalArea += w * h;
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

void func(CReactangle temp){
    temp.Print();
}

int main(){
    CReactangle r1(3,5);
    r1.Print();
    CReactangle r2 = r1;
    r2.Print();
    CReactangle r3(r2);
    r3.Print();
    // the three above use copy constructor, so if we dont code copy constructor
    // ourself, static vars will not change and now these three changed, cauze
    // we code copy constructor ourselves
    func(CReactangle(10,100)); // the temp-value will be killed with 
    // the end of func
    CReactangle r4(4,5);
    r4.Print();
    return 0;
}

/*
TotalArea = 15, Totalnum = 1
TotalArea = 30, Totalnum = 2
TotalArea = 45, Totalnum = 3
TotalArea = 1045, Totalnum = 4
TotalArea = 65, Totalnum = 4
*/