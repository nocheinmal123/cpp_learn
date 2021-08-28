#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class CTest{
    private:
        int n;
    public:
        explicit CTest(int x);
        int GetValue() const; //const member func
        int GetValue(); // reload of member func, non-const
};

CTest::CTest(int x){
    n = x;
}

int CTest::GetValue() const{
    return n;
}

int CTest::GetValue(){
    n = n * 2;
    return n;
}

int main(){
    const CTest c1(10);
    printf("v = %d\n",c1.GetValue()); // automatically using of const member func
    CTest c2(100);
    printf("v = %d\n",c2.GetValue()); // automatically using of non-const member func
    return 0;
}