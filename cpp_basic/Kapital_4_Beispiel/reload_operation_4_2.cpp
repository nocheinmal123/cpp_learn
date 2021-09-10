#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Time{
    private:
        int Hour;
        int Minute;
    public:
        Time(int h,int m):Hour(h),Minute(m){

        }
        Time& operator=(const Time& t);
};

Time& Time::operator=(const Time& t){
    Hour += t.Hour;
    Minute += t.Minute;
    return *this;
}

int main(){
    return 0;
}