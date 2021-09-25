#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
// 临时对象的产生和深入探讨
/*
++i: 返回的是左值，是i本身
i++: 先创造了一个临时对象用于保存和使用目的，再给i加上1，接着返回临时变量，再释放这个临时变量
我们可以通过右值引用，绑定这个临时变量，这样系统就不会再释放掉这个临时变量了
-fno-elide-constructors
*/

class CTempValue{
    private:
        int val1; int val2;
    public:
        CTempValue(int v1 = 0, int v2 = 0);
        CTempValue(const CTempValue& c);
        CTempValue& operator=(const CTempValue& c); 
        virtual ~CTempValue();
        int Add(CTempValue obj);
        void Print();
};

CTempValue::CTempValue(int v1, int v2):val1(v1),val2(v2){
    std::cout<<"con called"<<std::endl;
}

CTempValue::CTempValue(const CTempValue& c):val1(c.val1),val2(c.val2){
    std::cout<<"copy con called"<<std::endl;
}

CTempValue& CTempValue::operator=(const CTempValue& c){ //重载赋值运算符
    std::cout<<"reload ="<<std::endl;
    this->val1 = c.val1;
    this->val2 = c.val2;
    return *this;
}

CTempValue::~CTempValue(){ // virtual don't needed here
    std::cout<<"decon called "<<val1<<", "<<val2<<std::endl;
}

int CTempValue::Add(CTempValue obj){
    int temp = this->val1 + obj.val1;
    obj.val1 = 1000;
    return temp;
}

void CTempValue::Print(){
    std::cout<<"val1 = "<<val1<<std::endl;
}

int calc(const std::string& strsource, char ch){
    const char* p =strsource.c_str();
    int cnt = 0;
    // do some work
    return cnt;
}

int main(){
    int i = 1;
    int&& r = i++; std::cout<<r<<std::endl;
    r++; std::cout<<i<<std::endl;

    // 以下是会产生临时变量的四种情况：
    // 1.以传值的方式给函数传递参数
    CTempValue tm(10,20);
    int sum = tm.Add(tm);
    std::cout<<"sum = "<<sum<<std::endl;
    tm.Print();

    std::cout<<"---------------"<<std::endl;
    // 2.类型转换生成的临时变量/隐式类型转换以保证函数调用成功
    std::cout<<"***********************"<<std::endl;
    CTempValue c;  
    c = 1000; // 这里编译器作了隐式转换，将1000转换为一个临时对象
    std::cout<<"***********************"<<std::endl;
    CTempValue b = 200;
    
    std::cout<<"------------------------"<<std::endl;

    char text[] = "this is a test.";
    std::cout<<"func: "<<calc(text,'i')<<std::endl;
    // text是个char类型，而calc函数是个string的常引用，因此，系统会调用
    // string的构造函数，产生一个临时变量。注意，函数里面必须是常引用，因为
    // C++只会为常引用产生临时变量，系统不允许修改临时变量的这种行为发生
    // 如果去掉const，将导致编译错误。

    return 0;
}