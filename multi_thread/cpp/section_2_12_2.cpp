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
// std::timed_mutex: 带有超时功能的独占互斥量,如果超过一段时间拿不到锁，那么不会阻塞
        // try_lock_for()       在XX秒内，尝试加锁
        // try_lock_until()     参数是未来的一个时间点,在这个还没到的时间段之内，如果拿到锁了，就操作共享数据
                                // 如果时间到了，也走下来
// std::recursive_timed_mutex
class Sample{
    private:
        std::list<int> msgRecvQueue;
        // 创建一个互斥量
        std::timed_mutex mtx_;
    public:
        // 把收到的玩家命令加到一个队列的线程
        void inMsgRecvQueue() {
            for(int i = 0 ; i < 10000; i++) {
                // if (mtx_.try_lock_for(std::chrono::milliseconds(100))) { // 在100ms之内，拿到了锁
                //     std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                //     msgRecvQueue.push_back(i);
                //     mtx_.unlock();
                // } else {
                //     std::cout << "can't lock" << std::endl;
                //     std::this_thread::sleep_for(std::chrono::milliseconds(50));
                // }
                if (mtx_.try_lock_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(100))) { //尝试在接下来的100ms内，尝试上锁
                    std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                    msgRecvQueue.push_back(i);
                    mtx_.unlock();
                } else {
                    std::cout << "can't lock" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
            }
        }

        bool outMsgLULProc() {
            std::lock_guard<std::timed_mutex> que_guard(mtx_); // lock_guard构造函数调用了lock()
                                                              // 析构函数调用了unlock
                                                              // lock_guard的lock作用于它的整个生命周期内
            // que_mutex.lock(); //.empty()也会读数据，所以必须在这里就lock
            std::this_thread::sleep_for(std::chrono::milliseconds(105));
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