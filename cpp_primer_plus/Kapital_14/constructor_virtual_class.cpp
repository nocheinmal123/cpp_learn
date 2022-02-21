#include <iostream>
#include <string>
#include <memory>
#include <string.h>

class base0{
    public:
        int var0;
        base0(){
            std::cout << "default base0 con called.\n";
        }
        base0(int var):var0(var){
            std::cout << "base0 con called, var = " << var0 << std::endl;
        }
        void func0(){
            std::cout << "member of base0, var0 = " << var0 << std::endl;
        }
        ~base0(){}
};

class base1: virtual public base0{
    public:
        int var1;
        base1(int var):base0(var){
            std::cout << "base1 con called.\n";
        }
        void func1(){
            func0();
            std::cout << "func1.\n";
        }
        ~base1() {}
};

class base2: virtual public base0{
    public:
        int var2;
        base2(int var):base0(var){
            std::cout << "base2 con called.\n";
        }
        void func2(){
            func0();
            std::cout << "func2.\n";
        }
        ~base2() {}
};

class D1: public base1{
    public:
        int varD1;
        D1(int var):base0(var + 12), base1(var){
            std::cout << "D1 con called.\n";
        }
        ~D1(){}
};

class D2: public base2{
    public:
        int varD2;
        D2(int var):base0(var + 3), base2(var){
            std::cout << "D2 con called.\n";
        }
        ~D2(){}
};

class derived: public base1, public base2{
    public:
        int var;
        /*
        注意这里，C++在中间类是虚基类的时候，禁止信息通过中间类传给基类
        因为经过中间类A的这条路径将隐式调用基类构造函数一次，经过中间类B
        的这条路径将隐式调用基类构造函数一次，将导致二义性。所以必须显示
        地调用基类的构造函数，如果没有的话，编译器将会尝试调用基类的默认
        构造函数
        */
        derived(int var): base1(var), base2(var + 1), base0(var + 100){

        }
        ~derived(){}
        void func(){
            std::cout << "member of derived.\n";
            base1::func1();
        }
};

/*
虚基类子对象是由最远派生类的构造函数通过调用虚基类的构造函数进行初始化的。
最远派生类指的是，继承结构时，建立对象(或者指针或者引用)所用的类
*/

int main(){
    derived d(1);
    // d.var0 = 2;
    // d.base2::func0();
    // d.func1();
    // d.func2();
    d.func();
    D1 obj_d1(18);
    std::shared_ptr<D2> p_d2 = std::make_shared<D2>(81);
    p_d2->func0();
    p_d2->func2();
    return 0;
}