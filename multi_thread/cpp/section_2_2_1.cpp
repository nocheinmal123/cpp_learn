#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>

/**
 * join
 * detach
 * */

void myprint() {
    std::cout << "my thread starts processing" << std::endl;
    // work
    std::cout << "my thread ends.\n";
}

int main() {
    /**
     * 程序运行起来，生成了一个进程，该进程所属的主线程就开始自动地运行起来了
     * std::cout << "I Love China!" << std::endl; // 实际上是主线程在执行，主线程从main函数返回，则整个进程执行完毕 
     * 主线程从main开始执行，那么我们创建的线程也必须从一个函数开始执行,一旦这个函数运行完毕，就代表着这个线程运行完毕
     * 整个进程是否执行完毕的标志是主线程是否执行完毕，如果主线程完毕，那么进程完毕。此时，一般情况下，如果其他子线程还没执行完毕，
     * 那么这些子线程也会被操作系统强行终止，所以如果想保持子线程的运行状态，那么就要让主线程一直保持运行，不要让主线程运行完毕。
    */

   /**
    * 自己创建线程所需：
    * 头文件<thread>
    * 初始函数
    * */
   
   std::thread thread1(myprint); // 创建了线程，线程执行的入口是myprint函数
                                 // 这个线程就开始执行了
   thread1.join();               // join是加入/汇合的意思，也就是阻塞了主线程，让主线程等得子线程执行完毕，
                                 // 然后子线程和主线程汇合之后，汇合之后，主线程再继续往下走
                                 // 总结就是阻塞主线程，并等待thread1执行完
   std::cout << "I Love China!\n";

   /**
    * detach()用法，意思就是分离，detach之后，主线程就不在关联子线程了。
    * 此时这个子线程就会驻留在后台运行了。主线程跟该子线程失去联系，
    * 子线程就相当于被C++运行时库接管了，当这个子线程执行完毕后，由运行时库
    * 负责清理该线程相关的资源.
    * 注意，这时虽然主线程和该线程分离了，不再有关联了，但是，如果主线程结束
    * 那么整个进程也就结束了，于是该子线程也就结束了。换句话说，该线程会随着主线程
    * 结束而结束，因此也被称为守护线程
    * 在C++中，如果既不使用join也不使用detach，而是孤零零地定义一个线程，程序运行会报错
    * 也间接地证明了，detach的作用就是将该子线程设置为守护线程，会随着主线程结束，进程结束
    * 而一起结束。
    * 再重复一遍，detach之后，该子线程会在后台运行，但是一旦主线程结束了，进程退出了，该
    * 子线程也会结束!并不会自己还在后台一直执行
    * */



   /**
    * joinable()用法
    * 用来判断是否可以成功使用join或者detach的,返回true或者false
    * true表示可以join或者detach
    * false表示不可以join或者detach
    * */
   if (thread1.joinable() == true) {
       std::cout << "thread1 joinable == true.\n";
   } else {
       std::cout << "thread2 joinable == false.\n";
   }
   return 0;
}