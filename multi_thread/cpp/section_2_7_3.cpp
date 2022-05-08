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
 * std::call_once()
 * 
 * section_2_7_2.cpp中，看似那个double check已经没有问题了
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
        static std::once_flag once_flag_;
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
Singelton<Type>* Singelton<Type>::singelton_instance = nullptr;

// mutex初始化
template<typename Type>
std::mutex Singelton<Type>::mtx_;

// once_flag初始化
template <typename Type>
std::once_flag Singelton<Type>::once_flag_;


template <typename Type>
Singelton<Type>* Singelton<Type>::getInstance() {

    // 使用std::call_once解决
    std::call_once(once_flag_, [&]() {
        singelton_instance = new Singelton<Type>();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        static Deletor deletor;
    });
    return singelton_instance;


    // std::unique_lock<std::mutex> lock_(mtx_, std::defer_lock);
    // 我们再来看看下面这个代码
    /*
    singelton_instance = new Singelton<Type>();这句话并不是原子操作
    这句话其实分了三步
    1.开辟内存空间
    2.调用构造函数
    3.给singelton_instance赋值
    如果编译器是按照这个顺序来执行这句话是没有问题的，因为给singelton_instance赋值是在调用构造函数之后执行的
    但是如果编译器为了优化reorder了这三个步骤，变成了
    1.开辟内存空间
    2.给singelton_instance赋值
    3.调用构造函数
    就会产生问题。假设线程A执行到了给singelton_instance赋值
    此时发生了上下文切换，到了线程B执行
    线程B，一旦执行了最外层的if (singelton_instance == nullptr),发现singelton_instance不为nullptr，直接返回
    因为此时构造函数还未调用，导致得到了一个没有意义的指针
    */
   /*
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
    std::cout << "addr = " << static_cast<void*>(p_singelton) << std::endl;
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

    // std::call_once()
    // 第二个参数是个函数名a()
    // call_once能保证函数a只被调用一次
    // 具备互斥量能力，可以代替加锁的方案
    // 需要与std::once_flag结合使用，其实once_flag是一个结构
    // 这个函数就是通过这个once_flag来决定对应的函数a是否被执行了，一旦执行，就设置为已经调用
    // 后续再次调用call_once，发现once_flag被设置成了已调用，那么对应的函数a就不会再次执行了
    return 0;
}