#include <iostream>
extern int x;
namespace{  //编译器会自动生成一个匿名的名称空间，并且自动执行using编译命令
            //并且和static一样，指挥作用在本文件中
    int y = -4;
}

void another(){
    std::cout << "another: " << x << ", " << y <<std::endl;
}