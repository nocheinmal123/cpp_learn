#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>
// 懒汉式单例模式，解决方案二
// 使用静态局部变量
/*
原因是Magic Static特性。如果变量在初始化时，并发线程同时进入到static声明语句，
并发线程会阻塞等待初始化结束。这样可以保证在获取静态局部变量的时候一定是初始化过的，所以具有线程安全性，
同时也避免了new对象时指令重排序造成对象初始化不完全的现象。
并且相比较与使用智能指针以及mutex来保证线程安全和内存安全来说，这样做能够提升效率
*/

template <typename Type>
class Singelton {
    private:
        Singelton() {}
        ~Singelton() {}
        Singelton(const Singelton&) = delete;
        Singelton& operator=(const Singelton&) = delete;
    public:
        static Singelton& getInstance();
};

template <typename Type>
Singelton<Type>& Singelton<Type>::getInstance() {
    static Singelton<Type> instance;
    return instance;
}

void mythread() {
    std::cout << "my thread " << std::this_thread::get_id() << " begins.\n";
    Singelton<int>& instance = Singelton<int>::getInstance();
    std::cout << "addr = " << &(instance) << std::endl;
}

int main() {
    std::thread task1(mythread);
    std::thread task2(mythread);
    task1.join();
    task2.join();
    return 0;
}