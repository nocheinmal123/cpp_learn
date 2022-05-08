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
// std::packaged_task
// 模板参数是各种可调用对象，通过std::packaged_task来把各种可调用对象包装起来
// 方便之后作为线程入口函数来调用

int thread_sample(int num) {
    std::cout << "thread starts, id = " << std::this_thread::get_id() << std::endl;
    std::cout << "num = " << num << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "thread end, id  = " << std::this_thread::get_id() << std::endl;
    return 5;
}

std::vector<std::packaged_task<int(int)>> vec_task;

int main() {
    std::cout << "main thread, id = " <<std::this_thread::get_id() << std::endl;
    std::packaged_task<int(int)> pt(thread_sample); // 我们把函数thread_sample包装起来,有点类似于std::function
    std::thread task(std::ref(pt), 109); // 用std::thread创建的线程必须用join/detach
    std::future<int> res = pt.get_future(); 
    std::cout << res.get() << std::endl; // 这个get没有阻塞作用了，因为是std::thread开启的线程
    task.join();

    std::packaged_task<int(int)> pt_lamda([](int) -> int {
        std::cout << "lamda packaged" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return 8;
    });

    // 第一种写法，利用std::thread
    // std::thread task2(std::ref(pt_lamda), 333);
    // task2.join();
    // std::future<int> res_lambda = pt_lamda.get_future();
    // std::cout << res_lambda.get() << std::endl;

    // 第二种写法，直接调用，并不会产生新的线程，相当于函数调用
    // pt_lamda(33);
    // std::future<int> res_lambda = pt_lamda.get_future();
    // std::cout << res_lambda.get() << std::endl;


    vec_task.push_back(std::move(pt_lamda));
    auto it = vec_task.begin();
    auto pt_move = std::move(*it);
    vec_task.erase(it);
    std::thread task3(std::ref(pt_move), 79);
    task3.join();
    std::future<int> res_vec_task = pt_move.get_future();
    std::cout << res_vec_task.get() << std::endl;
    return 0;
}