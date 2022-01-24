#include "10_10_2.h"

int main(){
    Person one;
    Person two("Smythecraft");
    Person three("Dimwiddy", "Sam");
    one.show();
    std::cout << std::endl;
    two.show();
    two.FormalShow();
    three.FormalShow();
    return 0;
}