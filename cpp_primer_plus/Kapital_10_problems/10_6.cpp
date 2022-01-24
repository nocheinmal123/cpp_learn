#include "10_10_6.h"

int main(){
    Move m1(1,3);
    m1.showMove();
    Move m2(7.3, -12.7);
    Move m3 = m1.add(m2); 
    m3.showMove();
    m3.reset(-1, -1);
    m3.showMove();
    return 0;
}