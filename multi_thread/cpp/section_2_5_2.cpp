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
 * std::lock函数模板
 * 可以一次锁住两个或者两个以上的互斥量
 * 它不存在这种因为多个线程中锁的顺序问题产生的死锁的风险
 * 如果互斥量有一个没锁住，std::lock就释放了已经锁住的锁头，并且阻塞在第一把锁那里，不断地尝试同时锁多把锁头
 * 要么一个都没锁住，要么都锁住
 * 但是仍然需要unlock
 * */


class Sample{
    private:
        std::list<int> msgRecvQueue;
        // 创建一个互斥量
        std::mutex que_mutex;
        std::mutex que_mutex_;
    public:
        // 把收到的玩家命令加到一个队列的线程
        void inMsgRecvQueue() {
            for(int i = 0 ; i < 10000; i++) {
                std::lock(que_mutex, que_mutex_);
                std::lock_guard<std::mutex> que_guard_1(que_mutex, std::adopt_lock);    // 利用std::adopt_lock表示已经锁过了
                std::lock_guard<std::mutex> que_guard_2(que_mutex_,  std::adopt_lock);  // 用来标记这个互斥量已经lock过了，
                                                                                        // 不要在构造函数里面再次调用lock函数了
                                                                                        // 不需要手动unlock
                std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                msgRecvQueue.push_back(i);
                // que_mutex_.unlock();
                // que_mutex.unlock();
            }
        }

        bool outMsgLULProc() {
            std::lock(que_mutex_, que_mutex);
            std::lock_guard<std::mutex> que_guard_1(que_mutex, std::adopt_lock); // 利用std::adopt_lock表示已经锁过了
            std::lock_guard<std::mutex> que_guard_2(que_mutex_,  std::adopt_lock);
            if (!msgRecvQueue.empty()) {
                int command = msgRecvQueue.front();
                msgRecvQueue.pop_front();
                std::cout << "front = " << command << std::endl;
                // que_mutex.unlock();
                // que_mutex_.unlock();
                return true;
            }
            // que_mutex.unlock(); 
            // que_mutex_.unlock();
            return false;
        } 

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
    Sample x;
    std::thread outMsg(&Sample::outMsgRecvQueue, std::ref(x));
    std::thread inMsg(&Sample::inMsgRecvQueue, std::ref(x));
    outMsg.join();
    inMsg.join();
    return 0;
}
