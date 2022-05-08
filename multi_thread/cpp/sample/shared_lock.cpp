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
#include <shared_mutex>

/**
 * shared_mutex详解
 * shared_mutex是一种读写锁
 * mutex是一种完全排他的锁，而shared_mutex提供了两种访问权限
 * 共享：多个线程能共享同一互斥的所有权（如配合shared_lock）
 * 独占：多个线程能共享同一互斥的所有权（如配合shared_lock）
 * shared_mutex 通常用于多个读线程能同时访问同一资源而不导致数据竞争，但只有一个写线程能访问的情形。
 * 
 * 排他性锁定
 * lock
 * try_lock
 * unlock
 * 
 * 共享锁定
 * lock_shared
 * try_lock_shared
 * unlock_shared
 * 
 * 在读锁重入过程中，被写锁抢占可能会导致死锁
 * */

class ThreadSafeCounter {
    public:
        // 多个读线程可以获取读锁
        int get() const {
            std::shared_lock<std::shared_mutex> lck; 
            return value_;
        }

        // 只有一个写线程可以获取写锁
        void increment() {
            std::unique_lock<std::shared_mutex> lck;
            value_++;
        }

        // 只有一个重置线程可以获取写锁
        void reset() {
            std::unique_lock<std::shared_mutex> lck;
            value_ = 0;
        }
    private:
        mutable std::shared_mutex mtx_;
        int value_ = 0;

};

int main() {
    ThreadSafeCounter counter;
    auto increment_and_get = [&counter]() {
        for (int i = 0; i < 3; i++) {
            counter.increment();
            std::cout << "id = " << std::this_thread::get_id() << ", get = " << counter.get() << "\n";
        }
    };
    std::thread task1(increment_and_get);
    std::thread task2(increment_and_get);

    task1.join(); task2.join();
    return 0;
}
