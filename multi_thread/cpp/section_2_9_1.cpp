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
 * std::async  std::future
 * std::packaged_task
 * std::promis
 * */


int thread_sample() {
    std::cout << "thread starts, id = " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "thread end, id  = " << std::this_thread::get_id() << std::endl;
    return 5;
}

int main() {
    // std::async std::future 创建后台任务并返回值
    // 希望线程返回一个结果
    // std::async是个函数模板，用来启动一个异步任务，返回一个std::future对象（std::future是个模板类）
    // 启动一个异步任务就是自动创建了一个线程，并开始执行线程对应的入口函数
    // 这个std::future对象就包含了这个线程的返回结果,可以通过调用future的成员函数get()来获取
    // 也叫std::future提供一C++种访问异步操作结果的机制

    std::cout << "main thread, id = " <<std::this_thread::get_id() << std::endl; 
    std::future<int> res = std::async(thread_sample); // 线程已经启动
    std::cout << res.get() << std::endl; // 这句话会将主线程阻塞在这里，get有着join的作用
    // res.wait(); // 也会阻塞，但是不接受返回值,相当于join
    return 0;
}