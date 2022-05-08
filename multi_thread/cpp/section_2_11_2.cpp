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
#include <atomic>
// std::atomic和std::async深入谈

int thread_() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "mythread starts, id = " << std::this_thread::get_id() << std::endl;
    return 1;
}

int main() {
    std::cout << "main thread starts, id = " << std::this_thread::get_id() << std::endl;
    std::future<int> res = std::async(thread_); // 线程这里已经启动
    // std::cout << res.get() << std::endl;

    // std::thread如果系统资源紧张，那么创建线程可能会失败，那么执行std::thread时，整个程序会崩溃
    // std::async我们一般不称为创建线程，尽管它可以。我们一般叫创建一个异步任务
    // std::async和std::thread最大的不同在于，async有时并不创建线程

    // 1.如果你用std::launch::deferred来调用async，会怎么样？
    // deferred延迟调用，并且不创建新的线程，延迟到future对象调用get()或者wait()的时候才执行函数
    // 2.如果用std::launcher::async
    // 强制这个异步任务在新线程上面执行，这意味着系统必须创建一个线程来执行这个异步任务
    // 3.如果同时std::launch::deferred | std::launche::asyn 表示有可能是创建新线程并立即执行，
    // 也可能是没有创建新线程并延迟调用,延迟到res.get()，才开始执行入口函数
    // 4.不带额外参数，默认值就是std::launch::deferred | std::launche::asyn，和3一样，有系统自行决定

    // 那么系统是怎么自行决定的呢
    // 也就是std::async和std::thread的区别了
    // std::thread创建线程，如果系统资源紧张，创建线程失败，整个程序失败
    // std::async创建异步任务，可能创建也可能不创建线程，并且async调用方法很容易拿到入口函数的返回值
    // 如果系统资源限制
    // 1.如果用std::thread创建的线程太多，那么可能创建失败，系统报告异常
    // 2.如果用std::async，一般不会报异常

    // std::async不确定问题的解决
    // 所以判断std::async(thread_)这个任务到底是同步还是异步需要用到std::future的wait_for
    std::future_status status_ = res.wait_for(std::chrono::milliseconds(0));
    if (status_ == std::future_status::deferred) {
        std::cout << "system resource too small.\n";
        res.get(); //在这里执行
    } else {
        std::cout << "thread was already created, when std::future<int> res = std::async(thread_);\n";
        std::cout << res.get() << std::endl; //已经启动的线程阻塞在这里
        std::cout << "multiple threads\n";
    }

    return 0;
}