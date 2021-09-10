#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Time{
    private:
        static int mystatic;
        int Minute;
    public:
        static void mstafunc(int testvalue);
        int& setvalue(int m = 0);
        void Print();
};

int Time::mystatic = 12;

void Time::mstafunc(int testvalue){
    mystatic = testvalue;
    // Minute = testvalue; wrong, only static member var in static member func
}

int& Time::setvalue(int m){
    Minute = m;
    return this->mystatic;
}

void Time::Print(){
    std::cout<<mystatic<<std::endl;
    std::cout<<Minute<<std::endl;
}

int main(){
    Time mytime1;
    Time mytime2;
    mytime1.setvalue() = 100;
    mytime2.setvalue(7) = 20;
    mytime1.Print();
    mytime2.Print();
    return 0;
}