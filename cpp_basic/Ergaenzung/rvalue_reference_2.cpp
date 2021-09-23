#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
// std::move() function
// 这个函数就是把一个左值强制转换成一个右值，带来的结果就是一个右值引用可以绑定到这个
// 被强制转换过后的右值上去了，这个函数没有移动能力，真正的移动发生在把一个右值使用
// 拷贝函数或者赋值操作符赋值给一个左值的时候

void func(int&& brv){

}

int main(){
    int i = 10;
    // int&& ri = i; 不可以，i是个左值
    int&&ri = std::move(i);
    ri = 20;
    std::cout<<ri<<", "<<i<<std::endl;
    i = 25;
    std::cout<<ri<<", "<<i<<std::endl;
    func(std::move(i));

    int&& r1 = 100;
    int& r2 = r1;
    int&& r3 = std::move(r1);
    r1 = 68;
    std::cout<<r1<<", "<<r2<<", "<<r3<<std::endl;
    r3 = 1000;
    std::cout<<r1<<", "<<r2<<", "<<r3<<std::endl;

    std::cout<<"------------------------------"<<std::endl;
    std::string st = "this is a test";
    const char* p = st.c_str();                 //0x008ff9d8
    std::string def = std::move(st);
    const char* q = def.c_str();                //0x008ff9b4
    /*
    程序运行结果可以发现，st变成了空串，而def变成了"this is a test"。会误认为，std::move()拥有移动能力，
    能将st的内容移动到def中去，其实不是的。其实，整个std::move(st)就是个右值，而语句std::string def = std::move(std);
    会导致string这个类中的移动构造函数执行，而这个移动构造函数会把st的内容清空，并不是std::move把st清空了
    同时，string这个类比较尴尬，这个类设计上的问题会导致系统没有办法把st中对应的"this is a test"这一段内存
    的操作权转移给def，而是在内存上重新开辟空间，将"this is a test"复制进去
    */
    std::string str = "test2";
    std::move(str);
    std::cout<<str<<std::endl;                  //str没有清空，证明了std::move其实没有移动能力

    std::string str2 = "test3";
    std::string&& str_ref = std::move(str2);    //没有触发移动构造函数，只是将str2转换成右值，并绑定到右值引用上
    str2 = "LLLLL";
    std::cout<<str2<<", "<<str_ref<<std::endl;
    str_ref = "RRRRRR";
    std::cout<<str2<<", "<<str_ref<<std::endl;
    return 0;
}
