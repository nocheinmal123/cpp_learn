#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
/**
 * 传递类对象，智能指针作为线程参数
 * 如果需要修改类对象，必须使用std::ref
 * */

class Sample {
    private:
    public:
        mutable int _val;
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
        void set_val(int k) {
            _val = k;
        }
};

void myprint(const Sample& src) {
    src._val = 199; //不会影响主线程的myobj，如果不=采用std::ref
    std::cout << "in child thread, addr of src is " << &src << std::endl;
    std::cout << "in child thread " << std::this_thread::get_id() <<std::endl;
}

void myprint_pointer(std::unique_ptr<Sample> ptr) {
    ptr->set_val(1010);
}

int main() {
    Sample myobj(10);

    // std::thread task(myprint, myobj);
    // std::cout << myobj.get_val() << std::endl;
    // task.join();

    // std::thread task2(myprint, std::ref(myobj));
    // task2.join();
    // std::cout << myobj.get_val() << std::endl; // 利用了std::ref，完成了对类对象的修改

    std::unique_ptr<Sample> ptr(new Sample(1000));
    std::thread task3(myprint_pointer, std::move(ptr));
    task3.join();
    // std::cout << ptr->get_val() << std::endl; 已经被std::move了，不能再用了
    return 0;
}