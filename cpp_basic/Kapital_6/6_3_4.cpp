#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
class myclass{
    public:
        virtual void hello(){
            std::cout<<"hello from myclass"<<std::endl;
        }
        virtual void bye(){
            std::cout<<"bye from myclass"<<std::endl;
        }
};

class son: public myclass{
    public:
        void hello(){
            std::cout<<"hello from son"<<std::endl;
        }
        son(){
            hello(); // if local exists, using local func, it is also called "func hide"
        }
        ~son(){
            bye(); // if local dosen't exist, using same func from base class
        }
};

class grandson: public son{
    public:
        void hello(){
            std::cout<<"hello from grandson"<<std::endl;
        }
        void bye(){
            std::cout<<"bye from grandson"<<std::endl;
        }
        grandson(){
            std::cout<<"con grandson"<<std::endl;
        }
        ~grandson(){
            std::cout<<"decon grandson"<<std::endl;
        }
};

int main(){
    grandson gson;
    son* pson;
    pson = &gson;
    pson->hello();
    return 0;
}
/*
hello from son
con grandson
hello from grandson
decon grandson
bye from myclass
*/