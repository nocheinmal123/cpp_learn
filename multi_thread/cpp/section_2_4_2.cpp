#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>
std::vector<int> vec = {1, 3,12, 100, 3, 1};
// 共享数据
// 1.只读数据,是安全稳定的，不需要特别处理手段
// 2.可读可写

void myprint(int num) {
    std::cout << "thread-id = " << std::this_thread::get_id() << std::endl;
    std::cout << "vec[0] = " << vec[0] << " ," << "vec[1] = " << vec[1] << std::endl;
}

class Sample{
    private:
        std::list<int> msgRecvQueue;
        // 创建一个互斥量
        std::mutex que_mutex;
    public:
        // 把收到的玩家命令加到一个队列的线程
        void inMsgRecvQueue() {
            for(int i = 0 ; i < 10000; i++) {
                std::lock_guard<std::mutex> que_guard(que_mutex); //特殊用法，利用{}控制lock_guard的生命周期
                // que_mutex.lock();
                std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                msgRecvQueue.push_back(i);
                // que_mutex.unlock();
            }
        }

        bool outMsgLULProc() {
            std::lock_guard<std::mutex> que_guard(que_mutex); // lock_guard构造函数调用了lock()
                                                              // 析构函数调用了unlock
                                                              // lock_guard的lock作用于它的整个生命周期内
            // que_mutex.lock(); //.empty()也会读数据，所以必须在这里就lock
            if (!msgRecvQueue.empty()) {
                int command = msgRecvQueue.front();
                msgRecvQueue.pop_front();
                std::cout << "front = " << command << std::endl;
                // que_mutex.unlock(); //要在return之前unlock()
                return true;
            }
            // que_mutex.unlock(); //不要忘记这里的unlock()
            return false;
        }   //函数结束，局部对象que_guard析构，调用了unlock()

        void outMsgRecvQueue() {
            for(int i = 0 ; i < 10000; i++) {
                bool res = outMsgLULProc();
                if (res) {
                    std::cout << "outMsgRecvQueue() works, am element was poped.\n";
                } else {
                    std::cout << "outMsgRecvQueue() works, but msgRecvQueue is empty.\n";
                }
            }
        }
};

int main() {
    // 只读的例子
    std::vector<std::thread> thread_vec;
    for(int i = 0; i < 10; i++) {
        thread_vec.push_back(std::thread(myprint, i)); //创建10个线程，并且这10个线程已经开始执行
    }
    for(std::vector<std::thread>::iterator it = thread_vec.begin(); it != thread_vec.end(); it++) {
        it->join();
    }
    std::cout << "I Love China.\n";

    // 有读写的例子
    Sample x;
    std::thread outMsg(&Sample::outMsgRecvQueue, std::ref(x));
    std::thread inMsg(&Sample::inMsgRecvQueue, std::ref(x));
    outMsg.join();
    inMsg.join();


    // 互斥量
    /**
     * 基本概念：
     * 互斥量是个类对象，理解成一把锁。多个线程尝试用lock()成员函数来加锁这把锁头，只有一个线程都可以锁定成功
     * 成功的标志是lock()函数返回，如果没锁成功，那么流程就卡在lock()这里不断地去尝试锁这把锁头
     * lock()和unlock():
     * 用法是先lock()，再操作共享数据，再unlock(). lock()和unlock()必须要成对使用。
     * 为了防止大家忘记unlock，引入了一个叫std::lock_guard的类模板，可以直接取代lock()和unlock()
     * 也就是用了lock_guard，不能再使用lock和unlock了
     * 
     * */

    // 死锁
    /**
     * 基本概念：
     * 有两个线程A，B，两把锁lock_gold和lock_silver
     * 线程A执行的时候，这个线程会先锁住lock_gold，把lock_gold锁成功了，然然后再去锁lock_silver
     * 此时发生了上下文切换
     * 线程B执行，这个线程去锁lock_silver，因为lock_silver还没有被线程A锁住，所以能成功锁住lock_silver，于是线程B又接着想去锁lock_gold
     * 此时，死锁就发生了
     * 线程A因为拿不到lock_silver，代码执行不下去；线程B因为拿不到lock_gold所以代码也执行不下去了
     * 详情见section_2_5_1.cpp 和 section2_5_2.cpp
     * */
    return 0;
}