#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <functional>
/**
 * lambda表达式
 * lambda表达式完整声明格式如下:
 * [capture list] (params list) mutable exception-> return type { function body }
 * 1. capture list: 捕获外部变量列表
 * 2. params list: 形参列表
 * 3. mutable指示符: 用来说明是否可以修改捕获的变量
 * 4. exception: 异常设定
 * 5. return type: 返回类型
 * 6. function body: 函数体
 * 此外，我们还可以见到很多不完整声明的lambda表达式，常见如下几种
 * 1. [capture list](params list) -> return type {function body}
 * 2. [capture list](params list) {function body}
 * 3. [capture list]{function body}
 * 其中，
 * 格式1声明了const类型的表达式，这种类型表达是不能修改捕获列表中的值
 * 格式2省略了返回值类型，但是编译器可以推断出lambda表达式的类型：
 *      如果function body中存在return语句，那么lambda表达式的返回类型由return语句返回的类型确定
 *      如果function body中没有return语句，那么lambda表达式的返回类型是void
 * 格式3省略了参数列表，类似于普通函数中的无参函数
 * 
 * 同时，lambda表达式实质就是个函数指针
 * */

bool cmp(int x, int y) {
    return x < y;
}

int Add(int x, int y) {
    std::cout << "Add called.\n";
    return x + y;
}

int Minus(int x, int y) {
    return x - y;
}

int Operation(int x, int y, int(*hook_function)(int, int)) {
    return hook_function(x, y);
}

int main() {
    std::vector<int> vec1{3, 2, 1, 5, 7, 0};
    std::vector<int> vec2(vec1);
    sort(vec1.begin(), vec1.end(), cmp); //传统的方法，利用cmp函数指针
    for(int it: vec1) {
        std::cout << it << " ";
    }
    std::cout  << std::endl;

    sort(vec2.begin(), vec2.end(), [](int x, int y) -> bool {
        return x < y;
    });
    for(int it: vec2) {
        std::cout << it << " ";
    }
    std::cout  << std::endl;
    std::cout << "<========================================>\n";


    // 值捕获
    int a = 123;
    auto f_val = [a]() {
        // a = 78; 不能修改外部变量
        std::cout << "in lamda expression, a = " << a << std::endl;
    };
    a = 78; //外部变量的修改不会影响到lamda表达式内部捕获了的值，因为lamda内部已经拷贝了一份
    f_val();

    // 引用捕获
    // 按引用捕获，外部和lambda表达式内部会相互影响
    int b = 100;
    int c = 80;
    auto f_ref = [&b, &c]() {
        b = 90;
        std::cout << "in lamda expression, b = " << b << std::endl;
        std::cout << "in lamda expression, c = " << c << std::endl;
    };
    c = 70;
    f_ref();
    std::cout << "in main, b = " << b << std::endl;
    std::cout << "in lamda expression, c = " << c << std::endl;


    // 隐式值捕获
    // [=]表示外部所有的变量都是值捕获
    int m = 777;
    auto f_imp_val = [=] {
        std::cout << "in lamda expression, all value will be captured by val.\n";
        std::cout << m << std::endl;
    };
    f_imp_val();

    // 隐式引用捕获
    int n = 600;
    auto f_imp_ref = [&] {
        std::cout << "in lamda expression, all value will be captured by ref.\n";
        n = 10;
        std::cout << n << std::endl;
    };
    f_imp_ref();

    // 混合捕获
    /**
     * [] 不捕获任何外部变量
     * [var, ...] 默认以值得形式捕获指定的多个外部变量（用逗号分隔），如果引用捕获，需要显示声明（使用&说明符）
     * [this] 以值的形式捕获this指针
     * [=, &x] 变量x以引用形式捕获，其余变量以传值形式捕获
     * [&, x] 变量x以值的形式捕获，其余变量以引用形式捕获
     * */


    // 比较复杂的用法
    std::cout << "*************some complicated using method***********\n";
    auto k = [](int x) {
        return [](int y) {
            return y * 2;
        }(x) + 6;
    }(5);
    // 这里的k不再表示lambda函数的函数指针了，而是lambda函数立即按照参数(5)执行后，返回的结果了
    std::cout << "k = " << k << std::endl;

    std::cout << [](int x, int y) {
        return x + y;
    }(5,4) << std::endl;


    int x = 3, y = 10;
    std::cout << Operation(x, y, Add) << std::endl;
    std::cout << Operation(x, y, Minus) << std::endl;
    auto f = [](int x, int y) {
        return x * y;
    };
    std::cout << Operation(x, y, f) << std::endl;

    std::vector<std::function<void()>> vec_func;
    vec_func.emplace_back([]() {
        (*Add)(10, 20);
    });

    for(int i = 0; i < vec_func.size(); i++) {
        std::cout << "in the vec" << std::endl;
        vec_func[i]();
    }
    return 0;
}
