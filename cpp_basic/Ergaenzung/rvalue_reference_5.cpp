#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

class CTempValue
{
public:
    int val1;
    int val2;
    CTempValue(int v1 = 0, int v2 = 0);
    CTempValue(const CTempValue &c);
    CTempValue &operator=(const CTempValue &c);
    virtual ~CTempValue();
    int Add(CTempValue obj);
    void Print();
};

CTempValue::CTempValue(int v1, int v2) : val1(v1), val2(v2)
{
    std::cout << "con called " << val1 << ", " << val2 << std::endl;
}

CTempValue::CTempValue(const CTempValue &c) : val1(c.val1), val2(c.val2)
{
    std::cout << "copy con called " << val1 << ", " << val2 << std::endl;
}

CTempValue &CTempValue::operator=(const CTempValue &c)
{ //重载赋值运算符
    std::cout << "reload =" << std::endl;
    this->val1 = c.val1;
    this->val2 = c.val2;
    return *this;
}

CTempValue::~CTempValue()
{ // virtual don't needed here
    std::cout << "decon called " << val1 << ", " << val2 << std::endl;
}

int CTempValue::Add(CTempValue obj)
{
    int temp = this->val1 + obj.val1;
    obj.val1 = 1000;
    return temp;
}

void CTempValue::Print()
{
    std::cout << "val1 = " << val1 << std::endl;
}

CTempValue Double(CTempValue &ts)
{
    CTempValue tmp;
    tmp.val1 = ts.val1 * 2;
    tmp.val2 = ts.val2 * 2;
    // return CTempValue(ts.val1*2, ts.val2*2); // 优化， 减少了局部变量的开销
    return tmp;
}

int main()
{
    // 3.函数返回的时候会产生临时对象
    // CTempValue ts1(10,20);
    // Double(ts1);
    // std::cout << "--------------------" << std::endl;
    CTempValue ts2(100, 2);
    // CTempValue t = Double(ts2);
    // std::cout<<"####################"<<std::endl;
    CTempValue&& ref = Double(ts2); //通过绑定右值，延长了临时对象的生命周期
    std::cout<<"####################"<<std::endl;
    std::cout<<ref.val1<<"  "<<ref.val2<<std::endl;
    return 0;
}
/*
分别单独运行时的效果:
XXXXXXXXXXXXXXXXXXXX
--------------------
con called 100, 2           -->ts2
con called 0, 0             -->tmp con
copy con called 200, 4      -->返回值临时变量con 
decon called 200, 4         -->tmp decon
copy con called 200, 4      -->t
decon called 200, 4         -->返回值临时变量decon
decon called 200, 4         -->t
decon called 100, 2         -->ts2
##########################
con called 100, 2           -->ts2
con called 0, 0             -->tmp con
copy con called 200, 4      -->返回值连是变量con
decon called 200, 4         -->tmp decon
####################
200  4
decon called 200, 4         -->ref decon
decon called 100, 2         -->ts2 decon
*/