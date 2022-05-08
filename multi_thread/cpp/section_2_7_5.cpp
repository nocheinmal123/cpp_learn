#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>

// 饿汉式单例模式
// 在定义类的时候直接new
template <typename Type>
class Singelton {
    private:
        Singelton() {}
        ~Singelton() {}
        Singelton(const Singelton&) {}
        Singelton& operator=(const Singelton&) {}
        static Singelton<Type>* instance;

    public:
        static Singelton<Type>* getInstance();

        class Deletor {
            public:
                ~Deletor() {
                    if (Singelton<Type>::instance) {
                        delete Singelton<Type>::instance;
                        Singelton::instance = nullptr;
                        std::cout << "using deletor to delete instance.\n";
                    }
                }
        };
};

// 一开始就初始化
template <typename Type>
Singelton<Type>* Singelton<Type>::instance = new Singelton<Type>();


template <typename Type>
Singelton<Type>* Singelton<Type>::getInstance() {
    static Singelton<Type>::Deletor deletor;
    return instance;
}

void mythread() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "my thread " << std::this_thread::get_id() << " begins.\n";
    Singelton<int>* p_instance = Singelton<int>::getInstance();
    std::cout << "addr = " << static_cast<void*>(p_instance) << std::endl;
}

int main() {
    std::thread task1(mythread);
    std::thread task2(mythread);
    std::thread task3(mythread);
    task1.join();
    task2.join();
    task3.join();
    return 0;
}


