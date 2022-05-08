#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>
/**
 * 单例设计模式共享数据问题分析和解决
 * */


template <typename Type>
class Singelton {
    private:
        Singelton() {}
        ~Singelton() {}
        Singelton(const Singelton&) = delete;
        Singelton& operator=(const Singelton&) = delete;
        static Singelton<Type>* singelton_instance;
        static std::mutex mtx_;
    public:
        static Singelton<Type>* getInstance();

        class Deletor {
            public:
                ~Deletor() {
                    if (Singelton<Type>::singelton_instance) {
                        delete Singelton<Type>::singelton_instance;
                        Singelton<Type>::singelton_instance = nullptr;
                    }
                }
        };

};

template <typename Type>
Singelton<Type>* Singelton<Type>::singelton_instance;

template <typename Type>
std::mutex Singelton<Type>::mtx_;


template <typename Type>
Singelton<Type>* Singelton<Type>::getInstance() {
    std::unique_lock<std::mutex> lock_(mtx_, std::defer_lock);
    // double check,防止锁被乱用，每次都会锁一下再解锁，不管singelton_instance是不是nullptr
    // 但是实际上只是在创建的时候锁住就行
    if (singelton_instance == nullptr) {
        lock_.lock();
        if (singelton_instance == nullptr) {
            singelton_instance = new Singelton<Type>();
            static Deletor deletor;
        }
        lock_.unlock();
    }
    return singelton_instance;


    /*
    if (singelton_instance == nullptr) {
        // 线程A进入了这个if，突然被挂起了
        // 此时发生了上下文切换
        // 由于线程A还没没来得及new就挂起了，导致线程B也会进入了这个if，然后线程B执行了new，
        // 上下文切换
        // 线程A继续执行，也执行了new语句
        // 所以需要上锁
        singelton_instance = new Singelton<Type>();
        static Deletor deletor;
    }
    return singelton_instance;
    */
}

void mythread() {
    std::cout << "my thread begins.\n";
    std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
    Singelton<int>* p_singelton = Singelton<int>::getInstance();
    std::cout << "my thread ends.\n";
}

int main() {
    //  单例设计模式共享数据问题分析和解决
    // 面临的问题，需要我们自己创建的线程（而不是主线程）中来创建单例类的对象，这种线程会有很多
    // 所以getInstance()需要互斥
    std::thread task1(mythread);
    std::thread task2(mythread);
    task1.join();
    task2.join();
    return 0;
}