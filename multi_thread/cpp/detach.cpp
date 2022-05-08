#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <thread>
#include <time.h>
#include <unistd.h> 

void write_file() {
    std::ofstream File;
    File.open("/home/nio/private/cpp_learn/multi_thread/detach.txt", std::ios::app);
    int k = 10;
    while(k--) {
        File << k << "\n";
        std::cout << "k = " << k << std::endl;
    }
    File.close();
}

int main() {
    std::thread thread_file(write_file);
    thread_file.detach();
    std::cout << "main ends" << std::endl;
    return 0;
}