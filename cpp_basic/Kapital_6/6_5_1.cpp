#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
// virtual decon func
// use a pointer, which points at a obj of the derived class, normally
// only the decon of the base class will be called, but we know that, 
// the decon of dericed class should be called firstly and then the decon
// of base class, so how can we fix that?
// set the decon of base class as "virtual decon"
// In the meanwhile, the decon of the derived class can be non-virtual

// normally, if the class has the virtual func, its decon should be
// virtual, but "con func" can not be virtual !!!!

class son{
    public:
        virtual ~son(){
            std::cout<<"bye from son"<<std::endl;
        }
};

class grandson: public son{
    ~grandson(){
        std::cout<<"bye from grandson"<<std::endl;
    }
};

int main(){
    son* pson;
    pson = new grandson();
    delete pson; // only output "bye from son", the decon of derived class 
    // isn't been called, if no "virtual"
    return 0;
}