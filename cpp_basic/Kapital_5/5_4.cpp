#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Bug{
    private:
        int nLegs;
        int nColor;
    public:
        int nType;
        Bug(int legs,int color);
        void PrintBug();
        ~Bug(){
            std::cout<<"base decon called"<<std::endl;
        }
};

Bug::Bug(int legs,int color):nLegs(legs),nColor(color){
    std::cout<<"base con"<<std::endl;
}

void Bug::PrintBug(){
    std::cout<<"base "<<nType<<std::endl;
    std::cout<<"base Printbug"<<std::endl;
}

class FlyBug: public Bug{
    private:
        int nWings;
    public:
        FlyBug(int legs,int color,int wings);
        int PrintLegs() const;
        ~FlyBug(){
            std::cout<<"derived decon called"<<std::endl;
        }
};

FlyBug::FlyBug(int legs,int color,int wings):Bug(legs,color),nWings(wings){
    // must use "list initialization", cauz the private vars of 
    // father class cant be visited
    std::cout<<"derived con"<<std::endl;
}

int main(){
    FlyBug fb(2,3,4);
    fb.nType = 1;
    fb.PrintBug();
    // fb.nLegs = 2; wrong, nLegs is private

    // When creating the derived obj, the con-func of father class
    // will be called to initialize the member-var, which are derived
    // from the father class
    // The con-func of father class will be called firstly, then the con-func of son class
    // Method:
    // derived::derived(arg_derived-list):base(arg_base-list)

    //Firstly the decon of son class, then decon of father class
    return 0;
}
/*
base con
derived con
base 1
base Printbug
derived decon called
base decon called
*/