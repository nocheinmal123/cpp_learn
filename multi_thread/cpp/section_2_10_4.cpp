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
// std::atomic 原子操作
// 原子操作由于其不可分割性，因此不会被打断，因此共享数据是安全的，不存在中途被切到另外的线程上的问题
// 但是互斥量可以针对代码段，可以锁住代码段
// 原子操作只能针对一个变量
// 互斥量：多线程中用来保护共享数据的，锁上，再操作共享数据，再解锁
// 抛出问题：有两个线程，对同一个变量进行操作，一个线程读取变量，另外一个线程往这个变量中写值


std::atomic<bool> thread_ifend(false); //线程退出标记



void thread_() {
    std::chrono::milliseconds dura(1000);
    while(thread_ifend ==  false) {
        // 系统没要求线程退出
        std::cout << "thread id = " << std::this_thread::get_id() << " is working.\n";
        std::this_thread::sleep_for(dura);
    }
    std::cout << "thread id = " << std::this_thread::get_id() << " ends.\n";
    return;
}

int main() {
   
    std::thread task1(thread_);
    std::thread task2(thread_);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    thread_ifend = true;
    std::cout << "both ends.\n";
    task1.join(); task2.join();


    return 0;
}