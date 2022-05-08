#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>
// 死锁
    /**
     * 基本概念：
     * 有两个线程A，B，两把锁lock_gold和lock_silver
     * 线程A执行的时候，这个线程会先锁住lock_gold，把lock_gold锁成功了，然然后再去锁lock_silver
     * 此时发生了上下文切换
     * 线程B执行，这个线程去锁lock_silver，因为lock_silver还没有被线程A锁住，所以能成功锁住lock_silver，于是线程B又接着想去锁lock_gold
     * 此时，死锁就发生了
     * 线程A因为拿不到lock_silver，代码执行不下去；线程B因为拿不到lock_gold所以代码也执行不下去了
     * 解决方法：
     * 使得两个线程锁的顺序相同
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
                que_mutex.lock();   // 先锁que_mutex
                // 业务上第一段要保护的共享数据
                que_mutex_.lock();
                // 业务上第二段要保护的共享数据
                std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                msgRecvQueue.push_back(i);
                que_mutex_.unlock();
                que_mutex.unlock();
            }
        }

        bool outMsgLULProc() {
            que_mutex_.lock();  // 先锁que_mutex_
            que_mutex.lock();
            if (!msgRecvQueue.empty()) {
                int command = msgRecvQueue.front();
                msgRecvQueue.pop_front();
                std::cout << "front = " << command << std::endl;
                que_mutex.unlock();
                que_mutex_.unlock();
                return true;
            }
            que_mutex.unlock(); 
            que_mutex_.unlock();
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
