#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>

// thread是个非常经典的函数式编程的例子
// 在函数式编程中，比如std::bind和std::thread，如果想用引用
// 必须用std::ref把参数包装起来，才能当引用使用，不然函数会自动先拷贝一份
// 传递临时对象作为线程参数

// 总结，不加强制转换会在子线程执行隐式转换，加了则会在主线程执行转换
// 1.若传递int这种基本类型参数，不要用阴引用，直接用值传递
// 2.若传递类对象，避免隐式类型转换。应该全部都在创建线程这一行，就构建出临时对象来，然后在线程函数参数里面用const 引用来接;
// 否则系统还会构造一次，造成浪费

// void myprint(const int& i, char* buf) {
//     std::cout << i << std::endl; // 注意，这里的const int& i,虽然是引用，但是如果打印地址可以看出，i和mvar的地址不同
//                                  // 也就是说创建thread过程中，实际是传值，而非引用
//     std::cout << buf << std::endl; // 指针是相同的地址，所以说指针在detach过程中，肯定会出问题
// }

class Sample {
    private:
        int _val;
    public:
        Sample(int val): _val(val) {
            std::cout << "con called.\n";
        }
        Sample(const Sample& src): _val(src._val) {
            std::cout << "copy con called.\n";
        }
        Sample(Sample&& src): _val(src._val) {
            std::cout << "move con called.\n";
        }
        ~Sample() {
            std::cout << "decon called.\n";
        }

};

void myprint_class(const int i, const Sample& src) {

}

void myprint(const int& i, const std::string& buf) {
     std::cout << buf << std::endl;
}

int main() {
    int mvar = 1;
    int &mvar_ref = mvar;
    char buf[] = "this is a test";
    // std::thread task1(myprint, mvar, buf); //貌似用上const std::string&就可以解决指针的问题了
    //                                        // 但是事实上存在mybuf都被回收了,main结束了，系统才把char*转成string
    //                                        所以需要手动“提前”转换

    // std::thread task1(myprint, mvar, std::string(buf));  // 这样用是安全的，可以用自己写的类来证明
                                                            // 用来证明，手动转换是先发生的，然后再传给线程
    // task1.join();
    // task1.detach();
    int mvar2 = 90;
    //  std::thread task2(myprint_class, mvar, mvar2);
    std::thread task2(myprint_class, mvar, Sample(mvar2)); //先手动转换一次
    // task2.join();
    task2.detach(); // 如果使用detach，会造成类似的问题，因为mvar2被销毁了,然后再生成变量传给thread
    std::cout << "I Love China.\n";
    return 0;
}