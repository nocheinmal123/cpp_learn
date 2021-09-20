#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
// catch, throw, try

int main(){
    // using try and throw
    double m,n;
    std::cin>>m>>n;
    try{
        std::cout<<"before diving."<<std::endl;
        if(n == 0) throw -1; // -1 will be throwed 
        else if(m == 0) throw -1.0;
        else std::cout<<m/n<<std::endl;
        std::cout<<"after diving"<<std::endl;
    }
    catch(double d){
        std::cout<<"catch(double)"<<d<<std::endl;
    }
    catch(...){ // here, -1 will be catched
        std::cout<<"catch(int)"<<std::endl;
    }
    std::cout<<"finished"<<std::endl;
    return 0;
}