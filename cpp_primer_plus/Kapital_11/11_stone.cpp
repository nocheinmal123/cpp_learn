#include "11_stonewt.h"

int main(){
    using namespace STONE;    
    Stonewt stone;      //create a Stonewt obj
    stone = std::move(19.7);       //use Stonewt(double) to convert 19.7 to Stonewt
    // 程序将使用Stonewt(double)这个构造函数来创建一个临时的Stonewt的obj， 
    // 再通过重载=函数，将临时变量赋值给stone对象
    // 要想这种情况不发生，即不通过单一参数隐式的产生临时变量，应该是用explicit修饰单一参数构造函数
    // 或者多个参数（除去一个参数外，其他参数都有默认值）的构造函数
    Stonewt stone2 = std::move(20.1);       //这里的=是初始化的意思，所以会调用move copy con

    // 那么，如上可以得知，可以将一个double类型的变量自动转换成
    // 一个class的obj，那么可以将一个obj转换成基本类型的数据嘛
    // 比如：
    // Stonewt wolfe(285.7);
    // double host = wolfe;     possible?
    // 我们可以利用特殊的C++运算符函数 - 转换函数来做到
    /*
    double host = double(wolfe);
    double thinker = (double)wolfe;
    or implicit use of conversion function
    Stone wells(20,3)
    double star = wells
    */

    /*
    那么如何创建转换函数呢
    operator typename():
    
    缓缓函数必须是类方法
    转换函数不能指定返回类型
    转换函数不能有参数
    */
    Stonewt poppins(9, 2.8);
    // double p_wt = poppins; implicit conversion
    double p_wt = double(poppins); //explicit conversion
    std::cout <<"Convert to double, implicit:\n";
    std::cout << p_wt << std::endl;
    int p_int = int(poppins);
    std::cout <<"Convert to int, explicit:\n";
    std::cout << p_int << std::endl;

    int ar[20];
    Stonewt temp(14, 4);
    int Temp = 1;
    std::cout << ar[int(temp)] << std::endl; 
    // 如果不加explicit，你以为编译器会报错，从而让你发现粗你的笔误
    // 但是，编译器会做自动的隐式转换，自动将temp转为int类型
    // 从而，你就无法发现笔误
    return 0;
}