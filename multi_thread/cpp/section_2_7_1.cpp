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
 * 单例设计模式
 * 单例设计模式共享数据问题分析和解决
 * std::call_once()
 * */

/**
 * 单例设计模式
 * 整个项目中，有某个或者某些特殊的类，只能创建一个属于这个类的对象
 * */

template <typename Type>
class Singelton {
    private:
        // 私有化各种构造函数，不能直接生成对象
        Singelton() {}
        // 为什么不在Singelton自己的析构函数里面调用delete singelton_instance呢？
        // 因为singelton_instance是new出来的呀，需要手动调用delete去释放，delete会引起
        // Singelton析构函数的执行.所以你在Singelton里面写了delete singelton_instance
        // 在逻辑上就是没搞清楚谁先谁后的问题
        ~Singelton() {}
        Singelton(const Singelton&) = delete;
        Singelton& operator=(const Singelton&) = delete;
        // 创建一个static Type的指针，属于lazy singelton,懒汉式（在定义类的时候不去创建对象，而是等需要的时候再chuangjian）
        static Singelton<Type>* singelton_instance;
    public:
        static Singelton<Type>* getInstance();

        // 类套类，用来释放singelton_instance
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
// 初始化成nullptr 
template <typename Type>
Singelton<Type>* Singelton<Type>::singelton_instance = nullptr;

template <typename Type>
Singelton<Type>* Singelton<Type>::getInstance() {
    if (singelton_instance == nullptr) {
        singelton_instance = new Singelton<Type>();
        static Deletor deletor;
    }
    return singelton_instance;
}

int main() {
    // 以下两个地址是一样的，实现了单例
    Singelton<int>* p_singelton = Singelton<int>::getInstance();
    std::cout << static_cast<void*>(p_singelton) << std::endl;
    Singelton<int>* p_singelton_ = Singelton<int>::getInstance();
    std::cout << static_cast<void*>(p_singelton) << std::endl;
    return 0;
}