#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Demo{
    int id;
    public:
        Demo(int i);
        ~Demo();
};

Demo::Demo(int i){
    id = i;
    std::cout<<"id = "<<id<<" con"<<std::endl;
}

Demo::~Demo(){
    std::cout<<"id ="<<id<<" decon"<<std::endl;
}

Demo d1(1);
void Func(){
    static Demo d2(2);
    Demo d3(3);
    std::cout<<"in the func"<<std::endl;
}

int main(){
    Demo d4(4);
    d4 = 6;
    std::cout<<"main"<<std::endl;
    {
        Demo d5(5);
    }
    Func();
    std::cout<<"main ends"<<std::endl;
    return 0;
}

/*
id = 1 con
id = 4 con
id = 6 con
id = 6 decon
main
id = 5 con //th life of local var is fromt the declaration to the "}"
id = 5 decon
id = 2 con
id = 3 con
in the func
id = 3 decon
main ends
id = 6 decon // d4 = 6, first the local var of main dies, then the global var
id = 2 decon // late declaration, earlier death
id = 1 decon // earlier declaration, late death
*/