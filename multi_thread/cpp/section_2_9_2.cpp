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

class A {
    public:
        int thread_sample(int& num) {
            std::cout << "thread starts, id = " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            std::cout << "num = " << num << std::endl;
            num = 12;
            std::cout << "thread end, id  = " << std::this_thread::get_id() << std::endl;
            return 5;
        }
};

int main() {
    A a;
    int tmp = 1000;
    std::future<int> res = std::async(&A::thread_sample, std::ref(a), std::ref(tmp));
    printf("res = %d\n", res.get());
    std::cout << "tmp = " << tmp << std::endl;
    return 0;
}