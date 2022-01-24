#include <iostream>
#include "10_stock10.h"

int main(){
    using std::cout;
    cout << "Using constructors to create new objects\n";
    Stock stock1("NanoSmart", 12, 20.0);
    stock1.show();
    Stock stock2("Boffo Objects", 2, 2.1);
    stock2.show();

    cout << "Assigning stock1 to stock2:\n";
    stock2 = stock1;    //object assignment,默认复制方式是将
    // 成员赋值给另外一对象
    cout << "Listing stock1 and stock2:\n";
    stock1.show();
    stock2.show();

    cout << "Using a constructor to reset an object\n";
    stock1 = Stock("Nifty Foods", 10, 50.2);    // temp object，因为stock1已经存在
    // 所以这句话不是初始化语句，而是先构造了一个临时对象，再将临时对象赋值给stock1
    // 再将临时对象析构
    cout << "Revised stock1:\n";
    stock1.show();
    cout << "Done\n";

    // Stock stock3 = Stock("Stark Industrie", 78, 56.31);
    // 注意这种初始化方式，对于有的编译器，这种初始化等价于
    // Stock stock3("Stark Industrie", 78, 56.31);
    // 对于有的编译器，首先会调用构造函数，产生一个临时变量，然后调用
    // 复制构造函数将临时变量复制给stock3，再销毁临时变量

    Stock mystuff[4];   // create an array of 4 stock objs
    mystuff[3].show();
    const Stock tops = mystuff[2].topval(mystuff[1]);

    return 0;
}