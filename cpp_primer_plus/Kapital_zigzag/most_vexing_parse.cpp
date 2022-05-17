#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <functional>

// most_vexing_parse cpp中最烦人的细节

class Timer {
    public:
        Timer() {}
};

class TimeKeeper {
    public:
        TimeKeeper(const Timer& t) {}
        int get_time() {
            return 0;
        }
};

int fun(double double_val) {
    // int i(int(double_val)); //会报错

    // int i((int) double_val); //可以
    // int i(static_cast<int>(double_val)); // 可以
    int i{int(double_val)}; // 可以,利用{}初始化
    return i; //会报错
}


int main() {
    TimeKeeper time_keeper(Timer());
    double t = 3.15;
    // return time_keeper.get_time(); //会报错
}

/**
 * @brief 
 * TimeKeeper time_keeper(Timer());有两种解释
 * 1. 一个类型为TimeKeeper的变量名为time_keeper, 用Timer类的临时对象初始化
 * 2. 一个函数名为time_keeper的函数声明, 返回值类型为TimeKeeper, 并具有一个
 *  （未命名）参数, 该参数是指向函数的指针, 该函数返回Timer类型的对象
 * C++ 会按照第二种方式解释
 * 
 * 解决办法:
 * 1. TimeKeeper time_keeper((Timer()));
 * 2. TimeKeeper time_keeper = TimeKeeper(Timer());
 * 3. TimeKeeper time_keeper{Timer{}};
 *    TimeKeeper time_keeper(Timer{});
 *    TimeKeeper time_keeper{Timer()};
 */