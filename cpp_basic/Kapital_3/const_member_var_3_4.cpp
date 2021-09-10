#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Time{
    private:
        const int Hour;
        int Minute;
    public:
        Time(int h,int m);
};

Time::Time(int h,int m):Hour(h),Minute(m){
    // Hour = h; wrong, const member-var can only be initialized through
    // "list Initialzation"
}

int main(){
    Time time1(10,6);
    return 0;
}