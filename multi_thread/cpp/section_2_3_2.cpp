#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
// 线程id
/**
 * 线程id
 * 每个线程实际上都对应这个一个数字，每个线程都有着自己独一无二的id
 * std::this_thread::get()
 * */


class Sample {
    private:
        int _val;
    public:
        Sample(int val): _val(val) {
            std::cout << "con called.\n";
            std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
        }
        Sample(const Sample& src): _val(src._val) {
            std::cout << "copy con called.\n";
            std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
        }
        Sample(Sample&& src): _val(src._val) {
            std::cout << "move con called.\n";
            std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
        }
        ~Sample() {
            std::cout << "decon called.\n";
            std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
        }
        int get_val() const {
            return _val;
        }
};

void myprint(const Sample& src) {
    std::cout << "in child thread, addr of src is " << &src << std::endl;
    std::cout << "in child thread " << std::this_thread::get_id() <<std::endl;
}

int main() {
    int v1 = 12;
    int v2 = 90;
    std::cout << "main thread = " <<std::this_thread::get_id() << std::endl;
    // std::thread task(myprint, v2);
    std::thread task(myprint, Sample(v2));
    task.join();
    return 0;
}