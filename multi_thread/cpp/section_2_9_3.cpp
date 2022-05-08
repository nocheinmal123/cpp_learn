#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>

/**
 * std::launch::deferred表示线程入口函数调用会被延迟到std::future的wait或者get函数调用才执行
 * */
class A {
    public:
        int thread_sample(int& num) {
            std::cout << "thread starts, id = " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            std::cout << "num = " << num << std::endl;
            num = 12;
            std::cout << "thread end, id  = " << std::this_thread::get_id() << std::endl;
            return 5;
        }
};

int main() {
    A a;
    int tmp = 1000;
    std::future<int> res = std::async(std::launch::deferred, &A::thread_sample, std::ref(a), std::ref(tmp)); //线程没被创建
    std::cout << res.get() << std::endl; // 现在才开始执行
    // 如果参数传入的是 std::launch::async，那么就是声明的时候就回去创建新的线程
    // 系统默认使用的就是这个参数
    return 0;
}