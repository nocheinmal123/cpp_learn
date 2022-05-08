#include <iostream>
#include <mutex>
#include <future>
#include <thread>
#include <condition_variable>
#include <vector>
#include <numeric>

double work(const double* beg, const double* end, double init) {
    return std::accumulate(beg, end, init);
}

double Add(const std::vector<double>& vec) {
    using TaskType = double(const double*, const double*, double);
    std::vector<std::packaged_task<TaskType>> vec_pkg;
    std::vector<std::future<double>> vec_future;
    for(int i = 0; i < 2; i++) {
        vec_pkg.push_back(std::packaged_task<TaskType>(work));
        vec_future.push_back(std::move(vec_pkg[i].get_future()));
    }

    std::vector<std::thread> vec_task;
    const double* first_ = &vec[0];
    for(int i = 0; i < 2; i++) {
        if (i == 0) {
            vec_task.push_back(std::thread(std::move(vec_pkg[i]), first_, first_ + vec.size() / 2, 10));
        } else {
            vec_task.push_back(std::thread(std::move(vec_pkg[i]), first_ + vec.size() / 2, first_ + vec.size(), 7));
        }
    }

    std::vector<double> vec_res;
    for(int i = 0; i < 2; i++) {
        vec_res.push_back(std::move(vec_future[i].get()));
    }

    double ans = 0;
    for(int i = 0; i < 2; i++) ans += vec_res[i];
    for(int  i = 0; i < 2; i++) {
        vec_task[i].join();
    }
    return ans;
}

int main() {
    std::vector<double> vec{1, 2, 3, 4};
    std::cout << Add(vec) << std::endl;
}