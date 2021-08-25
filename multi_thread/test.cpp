#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <thread>

void Myprint(){
    std::cout<< "my thread begin "<<std::endl;
    std::cout<<"my thread end"<<std::endl;
    int num = 0;
    while(num<10){
        printf("num = %d\n",num++);
    }
}

void Proc(){
    int i = 0;
    while(i<50){
        printf("i = %d\n",i++);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

class Proc2{ //functor
    public:
        int &m_i;
        Proc2(int &i): m_i(i){
            std::cout<<"Construction function"<<std::endl;
        }
        Proc2(const Proc2 &proc2):m_i(proc2.m_i){
            std::cout<<"copy function"<<std::endl;
        }
        ~Proc2(){
            std::cout<<"destroy"<<std::endl;
        }
        void operator()(){
            std::cout<< "This is a class Proc2"<<std::endl;
            printf("m_i = %d\n",m_i);
        }
};

int main(){
    std::thread myjob(Myprint);
    std::thread th1(Proc);

    bool flag1 = myjob.joinable(); bool flag2 = th1.joinable();

    printf("flag1 = %d and flag2 = %d\n",flag1,flag2);
    th1.detach(); // detach: in the traditionall multithread programming, the main-thread must wait for all subthreads
    // and then exits. But using detach can break this tradition.
    // the connnection between th1 and main-thread will be lost. At this time, th1 will run
    // at the background of system. It is Daemon thread.

    myjob.join(); //join means it can here stops the main thread, until the Subthread is finished.
    flag1 = myjob.joinable(); flag2 = th1.joinable();
    printf("2:  flag1 = %d  flag2 = %d\n",flag1,flag2);

    int i = 5;
    Proc2 proc2(i); //i will be destroyed with main-thread, so the "m_i" in the class will be random
    std::thread th2(proc2);
    th2.detach();
    printf("Main thread end\n");
    return 0;
}