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

std::atomic<int> val;

void thread_write() {
    for(int i = 0; i < 1000000; i++) {
        val++;

        // val = val + 1; // 这个结果是不对的，这句不是原子操作，说明不是所有运算都是原子操作
        // 一般来说，针对这种++, --,+=,-=,&=,|=,*=,/=是支持的
    }
}

int main() {
    std::thread task1(thread_write);
    std::thread task2(thread_write);
    task1.join(); task2.join();
    std::cout << "val = " << val << std::endl;
    return 0;
}