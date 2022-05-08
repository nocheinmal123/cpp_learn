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


// std::promise 类模板
// 我们能够在某个线程中给它赋值，然后我们可以在其他线程中，把这个值得取出来

void thread_(std::promise<int>& promise_val, int num) {
    num++;
    num *= 10;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    promise_val.set_value(num); //结果保存到了promise_val中
    return;
}


void thread__(std::future<int>& res) {
    int num = res.get();
    std::cout << "threa__, id = " <<  std::this_thread::get_id() << std::endl;
    std::cout << "num = " << num << std::endl;
}


int main() {
    std::promise<int> promise_;
    std::thread task1(thread_, std::ref(promise_), 180);
    task1.join();

    std::future<int> res = promise_.get_future();
    // std::cout << res.get() << std::endl; //这个get没有阻塞作用，但是如果get在前，join在后，则get有阻塞作用
    std::thread task2(thread__, std::ref(res));
    task2.join(); //等threa__执行完毕
}