#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
// 成员函数参数作为线程入口

class Sample {
    private:
    public:
        int _val;
        Sample(int val): _val(val) {
            // std::cout << "con called.\n";
            // std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
        }
        Sample(const Sample& src): _val(src._val) {
            // std::cout << "copy con called.\n";
            // std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
        }
        Sample(Sample&& src): _val(src._val) {
            // std::cout << "move con called.\n";
            // std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
        }
        ~Sample() {
            // std::cout << "decon called.\n";
            // std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
        }
        int get_val() const {
            return _val;
        }
        void set_val(int k) {
            _val = k;
        }
        void thread_work(int num) {
            std::cout << "num = " << num << std::endl;
            std::cout << "child thread work works!\n";
        }
        void operator()(int num) {
            std::cout << "num = " << num << std::endl;
            std::cout << "in realod of operator.\n";
        }
};

int main() {
    Sample myojb(100);
    std::thread task(&Sample::thread_work, myojb, 14); // 类成员函数地址，类对象(事实上是this指针)，参数
    task.join();
    std::thread task2(myojb, 15);
    task2.join();
    return 0;
}