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
#define MAX_THREAD_NUM 5

/**
 * atomic详解
 * atomic_flag
 * atomic_flag可以用来代替锁,atomic_flag共有三种状态
 * 1. 未设置，即定义时未初始化
 * 2. 设置，置为true
 * 3. 清楚，置为false
 * 其中有test_and_set()和clear()两个成员函数
 * test_and_set()
 * 1.test表示先测试（读取当前atomic_flag的值）并返回个这结果值
 * 2.set表示将atomic_flag状态设置为ture
 * 3. 可以看出，test_and_set函数的返回值与set的结果没有关系，
 *    返回值只表示调用test_and_set函数前的atomic_flag当前的状态。
 *    调用此函数后atomic_flag状态一定为true
 * clear()
 * 清除标志
 * */

/**
 * 内存序
 * memory_order_relaxed
 * 不对执行顺序做保证，没有happens-before的约束，编译器和处理器可以对memory access做任何的reorder，
 * 这种模式下能做的唯一保证，就是一旦线程读到了变量var的最新值，那么这个线程将再也见不到var修改之前的值了
 * 
 * memory_order_acquire 和 memory_order_release
 * memory_order_acquire 当前线程中读或写不能被重排到此load前 ，常常和load一起使用
 *                      no reads or writes in the current thread can be reordered before this load.
 * memory_order_release 当前线程中的读或写不能被重排到此store后，常常和store一起使用
 *                      no reads or writes in the current thread can be reordered after this store.
 * 将资源通过store+memory_order_release的方式”Release”给别的线程；
 * 别的线程则通过load+memory_order_acquire判断或者等待某个资源，一旦满足某个条件后就可以安全的“Acquire”消费这些资源了
 * 
 * memory_order_acq_rel则是同时包含memory_order_acquire 和 memory_order_release
 * A read-modify-write operation with this memory order is both an acquire operation and a release operation. 
 * No memory reads or writes in the current thread can be reordered before the load, nor after the store. 
 * 也就是说所有read操作都在load之后，所有write操作都在store之前
 * 
 * memory_order_seq_cst
 * 该模型是最强的同步模式，同时也是默认的模型，具有强烈的happens-before语义
 * 
 * memory_order_consume不鼓励使用
 * 
 * 
 * 
 * 
 * 第二种分类：
 * Store 操作，可以选择 memory_order_relaxed, memory_order_release, memory_order_seq_cst
 * 
 * Load 操作，可以选择 memory_order_relaxed, memory_order_consume, memory_order_acquire, memory_order_seq_cst
 * 
 * Read-modify-write 操作，可以选择 memory_order_relaxed, memory_order_consume, memory_order_acquire, 
 * memory_order_release, memory_order_acq_rel, memory_order_seq_cst
 * */





std::atomic_flag mtx_ = ATOMIC_FLAG_INIT;
int val = 0;

void thread_write() {
    for(int i = 0; i <= 1000000;) {
        if (mtx_.test_and_set() == false) {
            val++;
            i++; // i++必须放在这里，因为原子假设if条件没有成立，代码会继续往下走
            // 原子操作不会阻塞，导致for循环中i++也会执行
            mtx_.clear();
        }
        // while(mtx_.test_and_set(std::memory_order_acquire));
        // val++;
        // mtx_.clear();
    }
}


int main() {
    std::vector<std::packaged_task<void()>> vec_pkg;
    for(int i = 0; i < MAX_THREAD_NUM; i++) {
        vec_pkg.push_back(std::packaged_task<void()>(thread_write));
    }
    std::vector<std::thread> vec_thread;
    for(int i = 0 ; i < MAX_THREAD_NUM; i++) {
        vec_thread.push_back(std::thread(std::move(vec_pkg[i])));
    }
    vec_pkg.clear();
    for(int i = 0; i < MAX_THREAD_NUM; i++) {
        vec_thread[i].join();
    }
    std::cout << "val = " << val << std::endl;
    return 0;
}