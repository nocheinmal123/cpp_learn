#include <string>
#include <string.h>
#include <thread>
#include <memory>
#include <time.h>
#include <iostream>
#include <vector>
// 等待和创建多个线程

void myprint(int num) {
    std::cout << "myprint starts.\n";
    std::cout << "myprint end.\n";
}

int main() {
    std::vector<std::thread> vec;
    for(int i = 0; i < 10; i++) {
        vec.push_back(std::thread(myprint, i)); //创建10个线程，并且这10个线程已经开始执行
    }
    for(std::vector<std::thread>::iterator it = vec.begin(); it != vec.end(); it++) {
        it->join();
    }
    std::cout << "I Love China.\n";
    return 0;
}