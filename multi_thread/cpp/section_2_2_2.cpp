#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>

// 其他创建线程的手法
// 1.类 2.lambda

class TA {
    public:
        // int& m_i; 直接用引用接受会造成主线程该变量销毁了，子线程还在用
        int m_i;
        TA(int &i):m_i(i) {
            std::cout << "con called.  ";
            std::cout << "adress m_i = " << &m_i << std::endl;
            std::cout << "threadid = " << std::this_thread::get_id() << std::endl;
        }
        TA(const TA& ta):m_i(ta.m_i) {
            std::cout << "copy con called.  ";
            std::cout << "threadid = " << std::this_thread::get_id() << std::endl;
        }
        ~TA() {
            std::cout << "decon called.  ";
            std::cout << "threadid = " << std::this_thread::get_id() << "\n";
        }
        void operator() () {
            std::cout << "thread operator begins.  ";
            std::cout << "threadid = " << std::this_thread::get_id() << "\n";
            std::cout << "1 m_i = " << m_i << std::endl;
            std::cout << "2 m_i = " << m_i << std::endl;
            std::cout << "3 m_i = " << m_i << std::endl;
            std::cout << "4 m_i = " << m_i << std::endl;
            std::cout << "5 m_i = " << m_i << std::endl;
            std::cout << "6 m_i = " << m_i << std::endl;
            std::cout << "thread operator ends.\n";
        }
};

int main() {
    // 用类创建
    int myi = 6;
    std::cout << "main thread adress m_ref = " << &myi << std::endl;
    TA ta(myi);
    std::thread thread1(ta); // ta是个可调用对象
                             // 注意，这里的thread1(ta)是会把ta深拷贝一份，然后子线程再利用这个副本的
    thread1.join();
    // thread1.detach(); // detach之后，主线程先结束了，传入的引用变成无效了
                         // 所以打印出的结果是不可预料的了
    std::cout << "I Love China!\n";


    // 用lamda表达式
    auto mylambda = [] {
        std::cout << "my lambda thread begins.\n";
        std::cout << "mu lambda thread ends.\n";
    };
    std::thread thread2(mylambda);
    thread2.join();
    return 0;
}