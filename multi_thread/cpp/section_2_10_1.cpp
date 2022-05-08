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
// future的其他成员函数

int thread_sample() {
    std::cout << "thread starts, id = " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "thread end, id  = " << std::this_thread::get_id() << std::endl;
    return 5;
}

int main() {

    std::cout << "main thread, id = " <<std::this_thread::get_id() << std::endl; 
    // std::future<int> res = std::async(thread_sample); 
    // std::cout << res.get() << std::endl;
    // std::future_status status = res.wait_for(std::chrono::milliseconds(1000)); // 等待1秒
    // std::future_status status = res.wait_for(std::chrono::milliseconds(6000)); // 等待6s

    std::future<int> res = std::async(std::launch::deferred, thread_sample);
    std::future_status status = res.wait_for(std::chrono::milliseconds(1000)); //如果前面明确是defered，那么这句话不会阻塞
    if (status == std::future_status::timeout) {   //等待1s，但是线程中需要执行5s
        std::cout << "thread doen't end after 1s" << std::endl;
    } else if (status == std::future_status::ready) {
        std::cout << "thread ends and returns" << std::endl;
        std::cout << "return val = " << res.get() << std::endl;
    } else if (status == std::future_status::deferred) {
        std::cout << "thread is deferred.\n";
        std::cout << res.get() << std::endl; // 线程这时才开始,其实是主线程开始执行
    }
    return 0;
}