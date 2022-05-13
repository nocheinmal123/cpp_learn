#include <functional>
#include <thread>
#include <memory>
#include <string>
#include <iostream>
// std::function详解


int Add(int x, int y) {
    std::cout << "Add called, x + y = " << x + y << std::endl;
    return x + y;
}

void void_func(int x, int y) {
    auto res = x + y;
    return;
}

class Functor {
    public:
        Functor(int x, int y) {

        }
        ~Functor() {}
        void operator()(double x) {
            std::cout << "I am functor, x = " << x << std::endl;
        }
};

class Sample {
    public:
        Sample(int x, int y) {}
        ~Sample() {}
        static int static_class_function(int m) {
            std::cout << "static function of class sample called.\n";
            return m*m;
        }
        int normal_class_function(int k, int p) {
            std::cout << "normal function of class sample called.\n";
            std::cout << "k = " << k << ", p = "<< p << std::endl;
            return k * 2;
        }
};

int main() {
    // 正常用法，调用普通函数
    std::function<int(int, int)> func_1 = Add;
    // 正用法，使用std::bind，这样的话，func_2本身不再需要参数，调用func_2时候就是固定调用Add(12, 30)
    std::function<int()> func_2 = std::bind(Add, 12, 30);
    std::function<int(int x, int y)> func_3 = std::bind(Add, std::placeholders::_1, std::placeholders::_2);
    std::cout << func_1(12, 20) << std::endl;
    std::cout << func_2() << std::endl;

    // 正常用法，调用仿函数，因为仿函数的特殊性，不需要利用std::bind，因为仿函数不需要this指针
    std::function<void(double)> func_6 = Functor(1, 2); //Functor()会产生一个临时对象
    func_6(12.3);


    // 非正常用法
    // 可以看出, std::function在定义的是时候，返回值类型不一定需要和函数指针保持一致,在某些情况下不保持一致
    // 不会报错
    // std::function其实会根据自己的返回值类型（也就是这里的void）去转发函数指针的返回值
    std::function<void(int, int)> func_4 = Add;
    // std::cout << func_3() << std::endl;
    func_3(34, 55);
    // 下面这种不保持一致会报错，因为std::function会自己判断到底能不能转发函数的的返回值
    // 也就是说，当函数有返回值的时候，function可以选择转发，也就是说如果非要写成<void(XX)>这种
    // 没有返回值的形式，也可以，这就不让std::function转发了
    // 但是如果函数没有返回值，std::function写成了带返回值的时候，会报语法错，如下所示
    // std::function<int(int, int)> func_4 = void_func; //不保持一致会报错


    // 正常用法，带std::bind
    // 本质上，下面func_5和func_1是等价的，std::bind实际上是用于，带部分写死参数的函数包装
    // 因此，std::bind更加泛型，所以当然允许全部都是不固定参数的，此时和不带std::bind的写法是等价的
    std::function<int(int x, int y)> func_5 = std::bind(Add, std::placeholders::_1, std::placeholders::_2);
    std::cout << func_5(100, 100) << std::endl;

    // 绑定类静态成员函数
    // 因为类静态成员函数是不需要this指针的，因此可以直接写，也可以利用bind，以下两种写法是等价的
    std::function<int(int)> func_7 = std::bind(&Sample::static_class_function, std::placeholders::_1);
    std::function<int(int)> func_8 = &Sample::static_class_function;
    std::cout << func_7(90) << std::endl;
    std::cout << func_8(1000) << std::endl;

    // 正常用法，绑定类成员普通函数
    Sample obj(56, 90);
    std::function<int(int, int)> func_9 = std::bind(&Sample::normal_class_function, 
                                                    &obj, 
                                                    std::placeholders::_1,
                                                    std::placeholders::_2);
    std::cout << func_9(90, 90) << std::endl;
    // 绑定类成员普通函数时，使用裸指针
    Sample* p_sample = &obj;
    std::function<int(int, int)> func_10 = std::bind(&Sample::normal_class_function, 
                                                    p_sample, 
                                                    std::placeholders::_1,
                                                    std::placeholders::_2);
    std::cout << func_10(91, 91) << std::endl;
    // 绑定类成员普通函数时，使用智能指针
    std::shared_ptr<Sample> sp_sample = std::make_shared<Sample>(91, 18);
    std::function<int(int, int)> func_11 = std::bind(&Sample::normal_class_function, 
                                                    sp_sample, 
                                                    std::placeholders::_1,
                                                    std::placeholders::_2);
    std::cout << func_11(92, 92) << std::endl;


    std::thread task1(std::bind(&Sample::normal_class_function,
                            sp_sample,
                            12,
                            20));
    task1.join();
    return 0;
}