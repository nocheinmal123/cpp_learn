#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// mutable, if we wanna change a non-const member-var in the
// const member-func, so what should we do?
// We can use "mutable" to do that
// But why we just delete the "const" of the member-func, so we can
// change the member-var in it? Because, the non-const member-func
// can't be called by const obj, we don't wanna this happen

class Time{
    private:
        mutable int myHour;
    public:
        explicit Time(int h = 0);
        void addone() const{
            myHour += 1;
        }
};

Time::Time(int h):myHour(h){

}

int main(){
    const Time time1;
    time1.addone();
     return 0;
}