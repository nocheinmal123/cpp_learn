#include <iostream>
#include <string>
#include <string.h>

/**
 * C++中的省略号和template结合使用
 * 以下部分内容摘自 https://zhuanlan.zhihu.com/p/356895741
 */

// 第一部分
template <typename Arg>
void func(Arg arg) {

}

template <>
void func(int x) {
    std::cout << "int version.\n";
}

template <>
void func(double x) {
    std::cout << "double version.\n";
}

template <typename Arg>
void pass(Arg arg) {
    func(arg);
}

template <typename ...Args>
void func_Dummy(Args ...args) {
    (func(args), ...);
    // 这种写法是将这条语句扩展成func(arg1), func(arg2), ... ,func(argN)
}

// 第二部分

template <typename Arg>
Arg returnFunc(Arg arg) {
    return arg * 2;
}

template <typename ...Args>
void calculate(Args&& ...args) {
    std::cout << "calculate function.\n";
}

template <typename ...Args>
void func_Dummy_(Args&& ...args) {
    calculate(returnFunc<Args>(args)...);
}

/**
 * 总结规则如下
 * 设args被声明为一个函数参数包，其扩展方式有
 * printArgs(args…)
 *      相当于printArgs(args1,args2,…,argsN)
 * printArgs(args)… 
        相当于printArgs(args1),…, printArgs(argsN)
 * (printArgs(args),0)…   逗号表达式
        这是一个逗号表达式
        相当于(printArgs(args1),0),…(printArgs(argsN),0)
 */

int main() {
    func_Dummy<int, double>(3, 10.2);
    func_Dummy_(1, 3.14);
    return 0;
}