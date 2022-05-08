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

int g_val = 0;
std::mutex g_mtx;
std::atomic<int> g_atomic_val {2};
// 或者std::atomic<int> g_atomic_val(2);

std::atomic<bool> thread_ifend(false); //线程退出标记

// void thread_write() {
//     for(int i = 0; i < 100000000; i++) {
//         // 加锁可以保证正确性，但是效率很低
//         std::unique_lock<std::mutex> lock_(g_mtx, std::defer_lock);
//         lock_.lock();
//         g_val++;
//         lock_.unlock();
//     }
//     return;
// }

void thread_write() {
    for(int i = 0; i < 100000000; i++) {
        g_atomic_val++;
    }
    return;
}


int main() {
    std::packaged_task<void()> pt_write_1(thread_write);
    std::packaged_task<void()> pt_write_2(thread_write);
    std::thread task_write_1(std::move(pt_write_1));
    std::thread task_write_2(std::move(pt_write_2));
    task_write_1.join(); task_write_2.join();
    std::cout << "g_atomic = " << g_atomic_val << std::endl;

    return 0;
}