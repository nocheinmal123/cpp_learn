#include <thread>
#include <functional>
#include <future>
#include <iostream>

// thread_local	是一个线程储存期修饰符
// 经过该修饰符修饰的关键字生命周期与线程生命周期一样
// 每个线程都有独一无二的一个thread_local变量
// 如果说static修饰的变量是全局唯一，那么thread_local就像是线程static，表示该线程唯一

/*
修饰全局变量
thread_local int val = 0;
std::mutex mtx_;

void thread_func() {
    // 每个线程都会拥有自己唯一的thread_local变量
    for (int i = 0; i < 3; i++) {
        val++;
        mtx_.lock();
        std::cout << "id = " << std::this_thread::get_id() << ", val = " << val << std::endl;
        mtx_.unlock();
    }
}*/

/*
修饰局部变量
std::mutex mtx_;
void thread_func() {
    for (int i = 0; i < 3; i++) {
        // 改成局部变量
        // thread_local的局部变量没有因为for循环作用域而重新赋值.
        // 这是因为线程存储期的变量都是和线程绑定的，所以只有第一次声明时被赋值.可以理解为线程的static变量.
        // 不过变量的作用域依然是在本身的作用域内.比如：在for循环外使用x就会编译时错误
        thread_local int val = 0;
        val++;
        mtx_.lock();
        std::cout << "id = " << std::this_thread::get_id() << ", val = " << val << std::endl;
        mtx_.unlock();
    }
}*/

std::mutex mtx;
class A {
    private:
        int counter = 0;
    public:
        A() {
            std::lock_guard<std::mutex> guard(mtx);
            std::cout << "create A" << std::endl;
        }
        ~A() {
            std::lock_guard<std::mutex> guard(mtx);
            std::cout << "destroy A" << std::endl;
        }
        int get_value() {
            return counter++;
        }
};

/*
thread_local修饰类
void thread_func() {
    for (int i = 0; i < 3; i++) {
        // 不论for循环了几次，每个线程只会生成一个指针
        thread_local A* p_A = new A();
        std::lock_guard<std::mutex> guard(mtx);
        std::cout << "id = " << std::this_thread::get_id() << ", counter = " << p_A->get_value() << std::endl;
    }
}*/


/*
A* create() {
    return new A();
}

void thread_func() {
    for (int i = 0; i < 3; i++) {
        // 但是如果采用这种先声明，再赋值的方法，就会产生多个,线程不唯一了
        thread_local A* a;
        a = create();
        std::lock_guard<std::mutex> guard(mtx);
        std::cout << "id = " << std::this_thread::get_id() << ", counter = " << a->get_value() << std::endl;
    }
}*/


class B {
    public:
        B() {
            std::lock_guard<std::mutex> guard(mtx);
            std::cout << "create B" << std::endl;
        }
        ~B() {}
        thread_local static int b_key_;
        static int b_static;
        int b_val_;
};

thread_local int B::b_key_ = 20;
int B::b_static = 15;

void thread_func() {
    B b;
    for (int i = 0; i < 3; i++) {
        b.b_key_--;
        b.b_static--;
        b.b_val_--;
        std::cout << "id = " << std::this_thread::get_id() << ", b_key_ = " << b.b_key_ << ", b_static = " << b.b_static << ", b_Val_ = " << b.b_val_ << std::endl;
    }
}

int main() {
    std::thread task1(thread_func);
    std::thread task2(thread_func);
    task1.join(); task2.join();

    /*
    总结
    1. thread_local描述的对象在thread开始时分配,而在thread结束时分解
    2. 一般在声明时赋值,在本thread中只执行一次
    3. 描述的对象依然只在作用域内有效
    4. 描述类成员变量时,必须是static的
    */
    return 0;
}