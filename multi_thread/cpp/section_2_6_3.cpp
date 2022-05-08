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
 * unique_lock所有权的传递
 * 一个mutex只和一个unique_lock进行绑定
 * std::move
 * return返回临时对象
 * */


class Sample{
    private:
        std::list<int> msgRecvQueue;
        // 创建一个互斥量
        std::mutex que_mutex;
    public:
        // 把收到的玩家命令加到一个队列的线程
        void inMsgRecvQueue() {
            for(int i = 0 ; i < 10000; i++) {

                std::unique_lock<std::mutex> que_lock(que_mutex, std::defer_lock); //创建了一个没有加锁的mutex


                /*
                所有权转移
                // que_lock可以把对que_mutex的所有权转移给其他unique_lock对象，但是不能复制！
                // std::unique_lock<std::mutex> que_lock2(que_lock); wrong，不能复制
                std::unique_lock<std::mutex> que_lock2(std::move(que_lock)); // 正确的，转移了所有权,移动语义
                                                                             // 此时que_lock指向了空，析构了，解锁了但同时que_lock2接管了mutex，又上锁了
                                                                             // 之后的解锁等操作都需要针对que_lock2了 
                */

                if (que_lock.try_lock()) {
                    // 拿到锁了，访问共享数据
                    std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                    msgRecvQueue.push_back(i);

                } else {
                    // 没拿到锁，做别的事情
                }

            }
        }

        bool outMsgLULProc() {
            std::unique_lock<std::mutex> que_lock(que_mutex);


            if (!msgRecvQueue.empty()) {
                int command = msgRecvQueue.front();
                msgRecvQueue.pop_front();
                std::cout << "front = " << command << std::endl;
                return true;
            }
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

    // unique_lock是个类模板，一般工作中使用lock_guard就够用了，但是特殊情况会使用unique_lock
    // lock_guard取代了mutex的lock()和unlock()
    return 0;
}


