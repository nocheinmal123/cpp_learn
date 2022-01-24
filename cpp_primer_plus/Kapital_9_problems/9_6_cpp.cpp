#include "9_6.h"
#include <iostream>
#include <memory>


void func(){
    using namespace Golf;
    char name[] = "tiger";
    std::shared_ptr<golf> pr = std::make_shared<golf>(name, 15);
    pr->showgolf();
    pr->sethandicap(80);
    pr->showgolf();
    pr->setgolf();
    pr->showgolf();
    pr->setgolf("kkk",0);
    pr->showgolf();
}

int main(){
    func();
    return 0;
}