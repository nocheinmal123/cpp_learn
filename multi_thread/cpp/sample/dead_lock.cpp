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

std::shared_mutex mtx;
int A = 0, B = 0;

void thread_1() {
    std::shared_lock<std::shared_mutex> lock_read_1(mtx);
    std::cout << "Thread 1 read source A = " << A << "\n";
    // 线程1执行到这里发生了上下文切换，切到了线程2
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    
    std::shared_lock<std::shared_mutex> lock_read_2(mtx);
    std::cout << "Thread 1 read source B = " << B << "\n";
}


void thread_2() {
    // 由于这里线程1还没有释放锁，线程2就一直尝试拿锁，线程1后面将不会被执行
    // 所以造成写锁无法拿到锁，读锁也无法释放锁
    // 也就是说线程1中由于线程2,一直无法unlock
    // 而线程2又必须等待线程1unlock
    std::unique_lock<std::shared_mutex> lock_write(mtx);
    A = 1;
    B = 1;
    // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Thread 2 is writing into source A and B\n";
}


int main() {
    std::thread task1(thread_1);
    std::thread task2(thread_2);
    task1.join(); 
    task2.join();
    return 0;
}