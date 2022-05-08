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
#include <assert.h>

/**
 * 内存序
 * memory_order_relaxed
 * 不对执行顺序做保证，没有happens-before的约束，编译器和处理器可以对memory access做任何的reorder，
 * 这种模式下能做的唯一保证，就是一旦线程读到了变量var的最新值，那么这个线程将再也见不到var修改之前的值了
 * 
 * memory_order_acquire 和 memory_order_release
 * memory_order_acquire保证本线程中,所有后续的读操作必须在本条原子操作完成后执行
 * memory_order_release保证本线程中,所有之前的写操作完成后才能执行本条原子操作
 * 将资源通过store+memory_order_release的方式”Release”给别的线程；
 * 别的线程则通过load+memory_order_acquire判断或者等待某个资源，一旦满足某个条件后就可以安全的“Acquire”消费这些资源了
 * 
 * memory_order_acq_rel则是同时包含memory_order_acquire 和 memory_order_release
 * 
 * memory_order_seq_cst
 * 该模型是最强的同步模式，同时也是默认的模型，具有强烈的happens-before语义
 * 
 * memory_order_consume不鼓励使用
 * */

std::atomic<std::string*> ptr;
int data = 0;

void producer() {
    std::string* str = new std::string("Hello");
    data = 42;
    ptr.store(str, std::memory_order_release); // 保证本线程中,所有之前的写操作完成后才能执行本条原子操作
}

void consumer() {
    std::string* str;
    while(!(str = ptr.load(std::memory_order_acquire))); // 保证本线程中,所有后续的读操作必须在本条原子操作完成后执行
    if (*str == "Hello") {  // 绝对保证
        std::cout << "str == Hello\n";
    }
    if (data == 42) {       // 绝对保证
        std::cout << "data == 42\n";
    }
}

int main() {
    std::thread task1(producer);
    std::thread task2(consumer);

    task1.join(); task2.join();
    return 0;
}