#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// compensite relation and Inheritance 
// The below is called compensite relation

class CPoint{
    private:
        double x,y;
    public:
        friend class CCircle;
};

class CCircle{
    private:
        double r;
        CPoint center;
};

/*

class CPoint{
    double x,y;
}

class CCircle:public CPoint{
    double r;
}
It is not suitable to use Inheritance here
*/



int main(){
    return 0;
}