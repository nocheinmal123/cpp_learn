#include <functional>
#include <iostream>
// std::bind使用
/**
 * std::bind返回值有两种
 * 取决于std::bind后面接的实际参数还是placeholder
 */

int add(int a, int b) {
    return a + b;
}

void minus(int a) {
    a -= 1;
}

auto test_bind() {
    int x = 10, y = 20;
    std::function<decltype(add(x, y))()> bind_func_1 = std::bind(add, x, y);
    /**
     * 此时bind_funce_1类似于如下
     * int bind_func_1() {
     *      return add(x, y);
     * }
     * 
     */
    printf("res of bind_func_1 = %d\n", bind_func_1());

    std::function<int(int, int)> bind_func_2 = std::bind(add, std::placeholders::_1, std::placeholders::_2);
    /**
     * 此时bind_funce_2类似于如下
     * int bind_func_2(int x, int y) {
     *      return add(x, y);
     * }
     * 
     */
    printf("res of binf_func_2 = %d\n", bind_func_2(x, y));


    std::function<decltype(minus(x))()> bind_func_3 = std::bind(minus, 101);
    return bind_func_1();
}

template <typename F, typename ...Args>
auto submit(F&& f, Args&&... args) {
    std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    return func();
}

int main() {
    std::cout << test_bind() << std::endl;
    printf("res sumit = %d\n", submit(add, 101, 20));
}