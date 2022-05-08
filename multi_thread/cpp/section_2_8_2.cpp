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

/**
 * std::condition_variabel()的深入思考
 * */
class Sample{
    private:
        std::list<int> msgRecvQueue;
        // 创建一个互斥量
        std::mutex que_mutex;
        std::condition_variable cond;
        static bool flag_;
    public:
        // 把收到的玩家命令加到一个队列的线程
        void inMsgRecvQueue() {
            for(int i = 0 ; i < 10000; i++) {

                std::unique_lock<std::mutex> que_lock(que_mutex);
                std::cout << "insert an element into msgRecvQueue, element = " << i << std::endl;
                msgRecvQueue.push_back(i);
                // 我们尝试把wait的线程唤醒（如果那个线程正在干活了，那么就没有效果了）
                // cond.notify_one(); //如果有多个线程卡在wait，那么通知任意的一个
                cond.notify_all();
            }
            flag_ = false;
        }


        void outMsgRecvQueue() {
            while (true) {
                std::unique_lock<std::mutex> que_lock(que_mutex);
                if (flag_ == false && msgRecvQueue.empty()) {
                    break;
                }
                // wait()是用来等一个东西，是cond的成员函数
                // 第一个参数是互斥量
                // 如果第二个参数的返回值是false，那么wait()将解锁互斥量，并阻塞本行，堵塞到其他某个线程调用notify_on这个函数为止
                // 如果没有第二个参数，那么就跟第二个参数返回false效果一样
                // 如果第二个参数的返回值是true，那么wait直接返回，代码继续往下执行
                
                // 当其他线程用notify_one将wait从阻塞的状态唤醒后
                // wait就恢复了，然后
                // wait会不断尝试重新获取互斥锁，如果获取到了锁，上锁，然后
                // 如果wait有第二个参数，则判断lamda表达式，如果表达式是false，wait又进行解锁，阻塞本行，进入休眠，等待再次被唤醒
                // 注意此时，如果wait没有第二个参数，因为之前的notify，那么wait就直接返回，代码继续执行（会引发虚假唤醒）

                cond.wait(que_lock, [this] {
                    if (!msgRecvQueue.empty()) 
                        return true;
                    return false;
                });

                // 如果表达式true，流程走下来,此时互斥锁一定是锁着的
                int res = msgRecvQueue.front();
                std::cout << "msgRecvQueue front was poped. " << std::this_thread::get_id() << "\n";
                msgRecvQueue.pop_front();
                que_lock.unlock(); //用来优化
                
                // 接下来处理一些非共享数据

            } // end while
        }
};

bool Sample::flag_ = true;

int main() {
    // std::condition_variable()
    // 线程A，等待一个条件满足
    // 线程B，专门往消息队列中发数据
    // std::condition_variable()实际上是一个类，和条件相关的类，需要和互斥量配合工作
    Sample x;
    std::thread task1(&Sample::inMsgRecvQueue, std::ref(x));
    std::thread task2(&Sample::outMsgRecvQueue, std::ref(x));
    std::thread task3(&Sample::outMsgRecvQueue, std::ref(x));
    task1.join(); task2.join(); task3.join();
}