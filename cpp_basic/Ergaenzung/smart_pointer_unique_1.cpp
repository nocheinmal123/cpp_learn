#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
/*
unique智能指针是一种独占式智能指针，也就是同一时刻，只有一个unqiue指针可以指向
这个对象（这块内存）。
unqiue<指向对象的类型名>智能指针变量名
*/

class A{
    public:
    A(){

    }
    ~A(){

    }
};

auto myfunc(){
    return std::unique_ptr<std::string>(new std::string("kkkk"));
}

int main(){
    // 常规初始化
    std::unique_ptr<int> p_1;
    if(p_1 ==  nullptr) std::cout<<"nullptr"<<std::endl;
    else std::cout<<"not nullptr"<<std::endl;
    std::unique_ptr<int> p_2(new int(1000));
    std::unique_ptr<int> p_3 = std::make_unique<int>(78);
    // 1.unique_ptr不支持的操作：复制，赋值
    // std::unique_ptr<int> p_4(p_1);
    // std::unique_ptr<int> p_4 = p_1;
    // std::unique_ptr<int> p_4;
    // p_4 = p_1;

    // 2.移动语义
    std::unique_ptr<std::string> ps(new std::string("this is a test."));
    std::unique_ptr<std::string> ps_2(std::move(ps));

    // 3.release成员函数
    /*
    放弃对指针的控制权（切断了智能指针和所指对象之间的联系），返回裸指针，
    将智能指针置空。返回的裸指针可以通过delete释放，也可以用来初始化另外
    一个智能指针或者给另外一个智能指针赋值
    */
    std::string* temp = ps_2.release();
    delete temp;

    // 4.reset成员函数
    /*
    当reset不带参数时，释放该智能指针指向的对象，并将智能指针置空
    当reset带参数时，释放该智能指针指向的对象，并将该智能指针指向新内存
    */
   std::unique_ptr<std::string> prs(new std::string("this is a test."));
   prs.reset();
   std::unique_ptr<std::string> prsdc(new std::string("a test"));
   std::unique_ptr<std::string> prsdc2(new std::string("test 2"));
    prsdc2.reset(prsdc.release());

    // 5. = nullptr;
    // 将智能指针所指向的对象释放，并将智能指针置空

    // 6.指向一个数组，会产生删除器问题
    std::unique_ptr<A[]> p_arr(new A[10]);

    // 7.get成员函数，返回裸指针
    auto* p_string = prsdc.get();
    const char* p_str = p_string->c_str();

    // 8.*解引用，获得p指向的对象

    // 9.swap成员函数

    // 10.智能指针名字作为判断条件

    // 11.转换成shared_ptr类型
    std::shared_ptr<std::string> ps_3 = myfunc();       //引用计数为1
    return 0;
}