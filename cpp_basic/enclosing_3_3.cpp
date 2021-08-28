#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class CTyre{
    private:
        int r,w;
    public:
    CTyre(int r,int w):r(r),w(w){ 
        std::cout<<"CTyre con called"<<std::endl;
    };
    ~CTyre();
};

CTyre::~CTyre(){
    std::cout<<"Ctyre decon called"<<std::endl;
}

class CEngine{
    public:
        CEngine(){
            std::cout<<"CEngine con called"<<std::endl;
        }
        ~CEngine(){
            std::cout<<"CEngine decon called"<<std::endl;
        }
};

class CCar{
    private:
        int price;
        CTyre tyre;
        CEngine engine;
    public:
        CCar(int p,int tr,int tw);
        ~CCar(){
            std::cout<<"CCar decon called"<<std::endl;
        }
};

CCar::CCar(int p,int tr,int tw):price(p),tyre(tr,tw){ // must using list to initialize
    std::cout<<"CCar con called"<<std::endl;
}

// wrong, cauz the var in class are just declaration, ther are not be
// defined yet
// CCar::CCar(int p,int tr,int tw){
//     this->price = p;
//     this->tyre = CTyre(tr,tw);
//     std::cout<<"CCar con called"<<std::endl;
// }

int main(){
    CCar car(5000,17,225);
    return 0;
}
// firstly the con of member-var, then the con
// decon and then the decon of member-var
/*
CTyre con called
CEngine con called
CCar con called
CCar decon called
CEngine decon called
Ctyre decon called
*/