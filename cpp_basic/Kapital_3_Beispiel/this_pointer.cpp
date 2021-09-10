#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Time{
    private:
        int Hour;
        int Min;
    public:
        explicit Time(int h = 0,int m = 0);
        Time& rtnhour(int tmphour);
        Time& rtnmin(int minute);
        void Print();
};

Time::Time(int h,int m):Hour(h),Min(m){

}

Time& Time::rtnhour(int tmphour){
    Hour += tmphour;
    return *this;
}

Time& Time::rtnmin(int minute){
    Min += minute;
    return *this;
}

void Time::Print(){
    std::cout<<Hour<<", "<<Min<<std::endl;
}

int main(){
    Time mytime(100);
    mytime.rtnhour(5).rtnmin(10);

    mytime.Print();

    int a = 10;
    int b = 20;
    int *const p = &a;
    *p = b; // it is fine
    std::cout<<*p<<std::endl;

    // p = &b; wrong
    const int *const pr = &a;
    // *pr = b; wrong
    // pr = &b; wrong
    return 0;
}

/*
in the normal member-fun, the "this pointer" is a const pointer,
such as "Time *const", which means, the pointer can't be changed, but
the ROM, which is been pointed, can be changed by it.
in the const memver-func (member func with const), "this pointer"
is "const Time* const"
*/