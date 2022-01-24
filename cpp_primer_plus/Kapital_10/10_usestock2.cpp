#include <iostream>
#include "10_stock10.h"

const int STKS = 4;

enum egg_old{
    Small,
    Medium,
    Large,
    Jumbo
};

enum class t_shirt{
    Small,
    Medium,
    Large,
    XLarge
};

enum class pizza: uint8_t{
    Small,
    Medium,
    Large,
    XLarge
};

int main(){
    Stock stocks[STKS] = {
        Stock("NanoSmart", 12, 20.0),
        Stock("Boffo Objects", 200, 2.0),
        Stock("Monolithic Obelisks", 130, 3.25),
        Stock("Fleep", 60, 6.5)
    };
    std::cout << "Stock holdings:\n";
    for(const auto& stk : stocks) stk.show();
    const Stock* top = &stocks[0];
    for(auto stk : stocks){
        top = &(top->topval(stk));
    }

    std::cout << "Top holding:\n";
    top->show();

    egg_old one = Medium;
    t_shirt rold = t_shirt::Large;
    int king  = one;        //allowed, implicit type conversion for unscoped
    // int ring = rolf;        //not allowed, no implicit type conversion
    if(king < egg_old::Medium){
        using namespace std;
        cout << "Jumbo converted to int before comparisino.\n";
    }
    // if(king < t_shirt::Medium){

    // } not allowed

    int Frodo = int(t_shirt::Small);    //scoped枚举需要使用显示类型转换

    return 0;
}