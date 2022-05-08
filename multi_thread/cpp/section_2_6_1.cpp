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
 * unique_lock取代lock_guard
 * unique_lock的第二个参数
 *      std::adopt_lock,表示这个互斥量已经lock了， 用来标记这个互斥量已经锁住了，用法和lock_guard中的相同
 *      std::try_to_lock,会尝试用mutex的lock去锁定这个mutex，但如果没有锁成功，也会立即返回，不会阻塞在那儿
 *      std::defer_lock
 * unique_lock成员函数
 *      lock()
 *      unlock()
 *      try_lock()
 *      release()
 * unique_lock所有权的传递
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
                // std::lock_guard<std::mutex> que_guard(que_mutex);  
                // std::unique_lock<std::mutex> que_lock(que_mutex);

                std::unique_lock<std::mutex> que_lock(que_mutex, std::try_to_lock);
                // 如果拿到了锁
                if (que_lock.owns_lock()) { 
                    std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                    msgRecvQueue.push_back(i);
                // 如果没有拿到锁
                } else {
                    // 没拿到锁,这块代码会立即执行
                }

                // std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                // msgRecvQueue.push_back(i);
            }
        }

        bool outMsgLULProc() {
            // std::lock_guard<std::mutex> que_guard(que_mutex); 
            std::unique_lock<std::mutex> que_lock(que_mutex);

            std::chrono::milliseconds dura(200);  // 1s = 1000ms
            std::this_thread::sleep_for(dura);      //在这里拿到锁了，会导致outMsg也在那儿卡住，因为拿不到锁了

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


