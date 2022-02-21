#include <iostream>
#include <string.h>
#include <string>

int main(){
    auto x = 5;                 // OK: x是int类型
    auto pi = new auto(1);      // OK: pi被推导为int*
    const auto *v = &x, u = 6;  // OK: v是const int*类型，u是const int类型
    static auto y = 0.0;        // OK: y是double类型
    // auto int r;                 // error: auto不再表示存储类型指示符
    // auto s;                     // error: auto无法推导出s的类型

    int x = 0;
    auto * a = &x;      // a -> int*，auto被推导为int
    auto   b = &x;      // b -> int*，auto被推导为int*
    auto & c = x;       // c -> int&，auto被推导为int
    auto   d = c;       // d -> int ，auto被推导为int
    const auto e = x;   // e -> const int
    auto f = e;         // f -> int
    const auto& g = x;  // g -> const int&
    auto& h = g;        // h -> const int&
    /*
    a 和 c 的推导结果是很显然的，auto 在编译时被替换为 int，因此 a 和 c 分别被推导为 int* 和 int&。
    b 的推导结果说明，其实 auto 不声明为指针，也可以推导出指针类型。
    d 的推导结果说明当表达式是一个引用类型时，auto 会把引用类型抛弃，直接推导成原始类型 int。
    e 的推导结果说明，const auto 会在编译时被替换为 const int。
    f 的推导结果说明，当表达式带有 const（实际上 volatile 也会得到同样的结果）属性时，auto 会把 const 属性抛弃掉，推导成 non-const 类型 int。
    g、h 的推导说明，当 auto 和引用（换成指针在这里也将得到同样的结果）结合时，auto 的推导将保留表达式的 const 属性

    如果是const+引用/const+指针推导的时候，const会被保留下来，如果知识const+一般类型，const会被丢弃
    */
    return 0;
}