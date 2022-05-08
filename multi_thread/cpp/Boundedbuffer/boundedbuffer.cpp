#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <string.h>
#include <vector>
#include <memory>
#define MAX_NUM 1000000

template <typename Type>
class Boundedbuffer {
    private:
        size_t write_cur_;
        size_t read_cur_;
        size_t buffered_;
        std::mutex mtx_;
        std::condition_variable cond_pro_;
        std::condition_variable cond_con_;
        std::unique_ptr<std::vector<Type>> container_;
        static bool end_flag_;
    public:
        explicit Boundedbuffer(size_t buffer_size);
        void Produce(const Type& T);
        void Consume();
};

template <typename Type>
Boundedbuffer<Type>::Boundedbuffer(size_t buffer_size) {
    write_cur_ = read_cur_ = buffered_ = 0;
    container_ = std::make_unique<std::vector<Type>>(buffer_size);
}

template <typename Type>
void Boundedbuffer<Type>::Produce(const Type& T) {
    for(int i = 0; i < MAX_NUM; i++) {
        std::unique_lock<std::mutex> lock_(mtx_);
        printf("Right now the %dth element insert, container size = %lu\n", i, container_->size());
        cond_pro_.wait(lock_, [this]() {
            return buffered_ < container_->size();
        });

        (*container_)[write_cur_] = T;
        // printf("Right now the %dth element insert, container size = %lu\n", i, container_->size());
        write_cur_ = (write_cur_ + 1) % container_->size();
        buffered_++;
        
        // 尝试通知消费者存进去数据了，可以取了
        cond_con_.notify_one();
    }
    end_flag_ = true;
}

template <typename Type>
void Boundedbuffer<Type>::Consume() {
    while(true) {
        if (buffered_ == 0 && end_flag_) break;
        std::unique_lock<std::mutex> lock_(mtx_);
        std::cout << "consume, buffered = " << buffered_ << std::endl;

        cond_con_.wait(lock_, [this]() {
            return buffered_ > 0;
        });

        Type res = (*container_)[read_cur_];
        printf("poped.\n");
        read_cur_ = (read_cur_ + 1) % container_->size();
        buffered_--;

        // 尝试通知生产者，有空余位置了，可以存数据了
        cond_pro_.notify_one();
    }
}

template <typename Type>
bool Boundedbuffer<Type>::end_flag_ = false;

int main() {
    Boundedbuffer<int> x(100);
    std::thread task_produce(&Boundedbuffer<int>::Produce, std::ref(x), 50);
    std::thread task_consume(&Boundedbuffer<int>::Consume, std::ref(x));
    task_produce.join(); task_consume.join();
    return 0;
}