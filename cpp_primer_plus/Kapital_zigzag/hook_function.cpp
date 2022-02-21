#include <iostream>
#include <string>
#include <string.h>

// 用法1：
template <typename T_>
bool compare(T_ x, T_ y) {
    return x < y;
}

template <typename T_>
void Sort(T_ x, T_ y, bool (*comp)(T_ x, T_ y)) {
    std::cout << "sort template" << std::endl;
    std::cout << comp(x, y) << std::endl;
}

// 用法2：

int add(int x, int y) {return x + y;}
int minus(int x, int y) {return x - y;}
int multi(int x ,int y) {return x * y;}

enum class FuncTYPE: int {
    ADD = 0,
    MIMUS,
    MULTI,
    DIV
};

typedef struct HookFunction {
    int (*handle_)(int, int);
};

HookFunction func[] = {
    {add},
    {minus},
    {multi}
};

int result(int x, int y, int (*pFunc)(int, int)) {
    return pFunc(x, y);
}

int main() {
    Sort(10, 3, compare);


    int a = 10, b = 2;
    std::cout << result(a, b, func[(int)FuncTYPE::ADD].handle_) << std::endl;
    std::cout << result(a, b, func[(int)FuncTYPE::MIMUS].handle_) << std::endl;
    std::cout << result(a, b, func[(int)FuncTYPE::MULTI].handle_) << std::endl;
    return 0;
}