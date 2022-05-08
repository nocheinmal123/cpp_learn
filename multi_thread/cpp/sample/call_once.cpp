#include <future>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <functional>
#include <condition_variable>

class Test {
    private:
        std::once_flag flag_;
    public:
        Test() {}
        ~Test() {}
        void thread_() {
            std::call_once(flag_, []() {
                std::cout << "call only once.\n";
            });
        }
};

int main() {
    std::vector<std::packaged_task<void()>> pkg_vec;
    Test t;
    for(int i = 0; i < 5; i++){
        pkg_vec.push_back(std::packaged_task<void()>(std::bind(&Test::thread_, std::ref(t))));
    }
    std::vector<std::thread> thread_vec;
    for(int i = 0; i < pkg_vec.size(); i++) {
        thread_vec.push_back(std::thread(std::move(pkg_vec[i])));
    }
    for(int i = 0; i < thread_vec.size(); i++) {
        thread_vec[i].join();
    }
    return 0;
}