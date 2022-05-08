#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
// recursive_mutex
class Sample{
    private:
        std::list<int> msgRecvQueue;
        // 创建一个互斥量
        std::mutex que_mutex;
        std::recursive_mutex mtx_;
    public:
        // 把收到的玩家命令加到一个队列的线程
        void inMsgRecvQueue() {
            for(int i = 0 ; i < 10000; i++) {
                std::lock_guard<std::mutex> que_guard(que_mutex); //特殊用法，利用{}控制lock_guard的生命周期
                std::lock_guard<std::recursive_mutex> lck_(mtx_);
                testfun1();
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

        void testfun1() {
            std::lock_guard<std::recursive_mutex> lck_(mtx_); //解决同一个线程中，同一个互斥量多次调用
        }
        void testfun2() {
            std::lock_guard<std::recursive_mutex> lck_(mtx_);
        }
};

int main() {
    // recursive_mutex 同一个线程可以多次锁,允许同一个线程中，同一个互斥量，被多次lock
    // std::mutex 自己拿到锁时，别人lock不了
    // std::timed_mutex: 带有超时功能的独占互斥量,如果超过一段时间拿不到锁，那么不会阻塞
        // try_lock_for()       等待一段时间
        // try_lock_until()       

    // 有读写的例子
    Sample x;
    std::thread outMsg(&Sample::outMsgRecvQueue, std::ref(x));
    std::thread inMsg(&Sample::inMsgRecvQueue, std::ref(x));
    outMsg.join();
    inMsg.join();

    return 0;
}