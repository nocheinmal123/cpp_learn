#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Bug{
    private:
        int nLegs; int nColor;
    public:
        int nType;
        Bug(int legs,int color);
        void PrintBug();
        ~Bug(){
            std::cout<<"decon Bug"<<std::endl;
        }
};

Bug::Bug(int legs,int color):nLegs(legs),nColor(color){
    std::cout<<"base con called"<<std::endl;
}

void Bug::PrintBug(){
    std::cout<<"nLegs = "<<nLegs<<std::endl;
    std::cout<<"nColor = "<<nColor<<std::endl;
    std::cout<<"nType = "<<nType<<std::endl;
}

class Skill{
    public:
        Skill(int n);
        ~Skill(){
            std::cout<<"Skill decon"<<std::endl;
        }
};

Skill::Skill(int n){
    std::cout<<"Skill con called"<<std::endl;
}

class FlyBug: public Bug{
    private:
        int nWings;
        Skill s1,s2;
    public:
        FlyBug(int legs,int color,int wings);
        ~FlyBug(){
            std::cout<<"FlyBug decon"<<std::endl;
        }
};

FlyBug::FlyBug(int legs,int color,int wings):Bug(legs,color),s1(legs),s2(color),nWings(wings){
    std::cout<<"Flybug con called"<<std::endl;
    // Skill s1(legs);
    // Skill s2(color);
}

int main(){
    FlyBug fb(1,2,3);
    return 0;
}
/*
base con called
Skill con called
Skill con called
Flybug con called
FlyBug decon
Skill decon
Skill decon
decon Bug
*/