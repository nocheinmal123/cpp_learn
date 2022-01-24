#include <string>
#include <string.h>
#include <iostream>
#include "12_1.h"

int main(){
    Cow c1("FANGSEN", "code", 90);
    c1.ShowCow();
    Cow c2;
    c2 = c1;
    c2.ShowCow();
    Cow c3("lvYILIN", "play old fang", 50);
    Cow c4(c3);
    c4.ShowCow();
    return 0;
}