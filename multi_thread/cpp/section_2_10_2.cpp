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
// std::futre的get会使用移动语义
// std::shared_future的get会复制数据
// 同时需要注意的是，std::packaged_task只支持移动语义，不支持复制
// 所以在使用的时候，比如std::thread绑定到某个packaged_task，必须用
// std::move或者临时变量的方法，而且，也就是说一packaged_task只能被
// 一个std:thread绑定
// 同时，std::thread也只支持移动语义

int thread_sample(int num) {
    std::cout << "thread starts, id = " << std::this_thread::get_id() << std::endl;
    std::cout << "num = " << num << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(8000));
    std::cout << "thread end, id  = " << std::this_thread::get_id() << std::endl;
    return 5;
}

/*
void thread__(std::future<int>& res) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    int num = res.get(); // 会阻塞在这里,同时主要这里的get使用移动语义
    std::cout << "threa__, id = " <<  std::this_thread::get_id() << std::endl;
    std::cout << "num = " << num << std::endl;
}
*/

void thread__(std::shared_future<int>& res) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    int num = res.get(); 
    std::cout << "threa__, id = " <<  std::this_thread::get_id() << std::endl;
    std::cout << "num = " << num << std::endl;
}

int main() {
    std::cout << "main thread, id = " <<std::this_thread::get_id() << std::endl;
    std::packaged_task<int(int)> pt(thread_sample); // 我们把函数thread_sample包装起来,有点类似于std::function
    std::thread task(std::ref(pt), 109); // 用std::thread创建的线程必须用join/detach
    std::future<int> res = pt.get_future(); 
    std::shared_future<int> shared_res(std::move(res));
    // 或者用std::shared_future<int> shared_res(res.share());
    // 或者std::shared_future<int> shared_res(pt.get_future());
    // std::thread task__(thread__, std::ref(res));

    // task.join();
    // task__.join();

    std::vector<std::packaged_task<void(std::shared_future<int>&)>> pkg_vec;
    for (int i = 0; i < 3; i ++) {
        pkg_vec.push_back(std::packaged_task<void(std::shared_future<int>&)>(thread__));
    }
    std::vector<std::thread> thread_vec;
    for (auto it = pkg_vec.begin(); it != pkg_vec.end(); it++) {
        auto pt_ = std::move(*it);
        thread_vec.push_back(std::thread(std::move(pt_), std::ref(shared_res)));
    }
    for (auto it = thread_vec.begin(); it != thread_vec.end(); it++) {
        auto task_ = std::move(*it);
        task_.join();
    }
    task.join();
    return 0;
}