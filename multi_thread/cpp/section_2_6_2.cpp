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
 *      std::defer_lock，初始化了一个没有加锁的mutex,也就是unique_lock构造的时候没有调用lock(),这是就配合unique_lock成员函数使用
 * unique_lock成员函数
 *      lock()      加锁
 *      unlock()    解锁. 如果不使用，解锁会发生在unique_lock对象析构的时候，使用这个能提前解锁
 *      try_lock()  尝试给互斥量加锁，如果拿不到返回false；如果拿到了，返回true
 *      release()   返回他所管理的原始的mutex对象的指针，并释放所有权，不再和那个mutex对象的指针有关系
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

                std::unique_lock<std::mutex> que_lock(que_mutex, std::defer_lock); //创建了一个没有加锁的mutex


                /*
                que_lock.unlock()
                处理非共享数据
                que_lock.lock()
                处理共享数据
                */
                // que_lock.lock();    // 利用lock成员函数加锁, 不用自己关心unlock()


                if (que_lock.try_lock()) {
                    // 拿到锁了，访问共享数据
                    std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                    msgRecvQueue.push_back(i);

                } else {
                    // 没拿到锁，做别的事情
                }

                // std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                // msgRecvQueue.push_back(i);


                /*
                release用法
                std::unique_lock<std::mutex> que_lock(que_mutex);
                std::mutex* mutex_ptr = que_lock.release(); // 解除关系，que_lock会变成nullptr
                // 操作共享数据
                mutex_ptr->unlock();  // 此时必须手动解锁了，因为release了
                */
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


