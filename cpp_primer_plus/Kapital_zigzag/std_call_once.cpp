#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <functional>
#include <future>
#include <condition_variable>


class Sample {
    private:
        int val_;
        static std::once_flag flag_;
        void sample_init() {
            std::cout << "sample init only once!\n";
        }
    public:
        void func() {
            std::cout << "func called\n";
            // 注意，就算在类的内部，也需要加上&Sample::和this指针
            // 因为这个被std::call_once调用函数是类的成员函数。如果是类的静态成员函数，则不用添加
            // 同理，packaged_task，包括std::function std::thread
            // std::call_once(flag_, &Sample::sample_init, this);
            // std::call_once(flag_, std::bind(&Sample::sample_init, this));
            
            std::call_once(flag_,[this]() {
                // this->sample_init(); 可以这么写
                // sample_init(); 可以这么写
                init_func();
            });

        }

        // 也需要加上&Sample::和this指针
        std::function<void()> init_func = std::bind(&Sample::sample_init, this);

        // 下面这种写法会被解释成函数, 而不是变量声明,包括std::thread也是
        /*std::packaged_task<void()> pkg([this]() {
            this->sample_init();
        });*/
        // std::thread task1(&Sample::sample_init, this);

        // 下面这两种写法可以
        // std::packaged_task<void()> pkg = std::packaged_task<void()>(std::bind(&Sample::sample_init, this));
        // std::thread task1 = std::thread(&Sample::init_func, this);
};

std::once_flag Sample::flag_;

void thread_func() {
    Sample s;
    s.func();
    s.func();
}

int main() {
    std::thread task1(thread_func);
    std::thread task2(thread_func);
    task1.join(); task2.join();
    return 0;
}
