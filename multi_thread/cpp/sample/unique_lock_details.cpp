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
/**
 * unique_lock整理
 * 如果第二参数是std::defer_lock
 *      try_lock 尝试加锁
 *      lock 加锁
 *      unlock 解锁
 *      release 释放
 * 如果第二个参数是std::try_to_lock // 表示这句话尝试加锁，如果没拿到，则继续往下走
 *      owns_lock == true 如果拿到锁了
 * */

/*
    release用法
    std::unique_lock<std::mutex> que_lock(que_mutex);
    std::mutex* mutex_ptr = que_lock.release(); // 解除关系，que_lock会变成nullptr
    // 操作共享数据
    mutex_ptr->unlock();  // 此时必须手动解锁了，因为release了

    注意在unlock之前，即使进行解除关系，释放操作，也一直处于加锁状态
*/

std::mutex mtx_;

void thread_function() {
    std::unique_lock<std::mutex> lck(mtx_, std::defer_lock);
    if (lck.try_lock()) {

    } else {

    }
    std::unique_lock<std::mutex> lck_(mtx_, std::try_to_lock);
    lck_.owns_lock();
}