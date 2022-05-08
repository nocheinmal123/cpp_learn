#include <functional>
#include <iostream>
#include <memory>
// 函数包装器，泛型编程思想
/**
 * @brief 
 * 函数包装，test函数能接受任意返回值，任意参数的函数，并且经过包装后，都能装换成void型无参函数进行调用
 * @tparam F type of fucntion
 * @tparam Args type of Arguments
 * @param f funciton
 * @param args arguments
 */

template <typename F, typename ...Args>
void test(F&& f, Args&&... args) {
    using res_type = decltype(f(args...));
    // 第一层封装，将“函数调用”这个过程，利用std::bind转换成一个返回值类型相同，但是无参的函数func
    std::function<res_type()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    // 将func用shared_ptr声明，方便第二层包装，这样就可以避免lambda函数裸指针传递给第二层包装，否则如果
    // 在这个函数中，裸指针析构掉了，会导致别的线程中该函数调用出现问题 
    std::shared_ptr<std::function<res_type()>> sp_func = std::make_shared<std::function<res_type()>>(func);
    res_type res;
    res_type res_2;
    // 第二层封装，将函数彻底封装成void型无参函数
    std::function<void()> wrapper_func = [sp_func, &res, func, &res_2]() {
        res = (*sp_func)();
        res_2 = func();
    };
    wrapper_func();
    std::cout << res << std::endl;
    std::cout << res_2 << std::endl;
}

int Add(int x, int y) {
    return x + y;
}

int main() {
    test(Add, 1, 3);
    // 比较下面两个用法
    std::function<int(int, int)> func = Add;
    // func_2是固定的，一旦调用func_2，相当于调用了Add(1, 2)
    std::function<int()> func_2 = std::bind(Add, 1, 2); 
    return 0;
}