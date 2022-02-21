#include "worker0.h"
#include <memory>
template <typename T>
class QueueTP{
    private:
        int size_;
        int top_;
        T* items_;
    public:
        explicit QueueTP(int size = 10){
            items_ = new T[size];
            top_ = 0;
        }
        ~QueueTP() { delete[] items_; }
        bool isFull() const;
        bool isempty() const;
        bool push(const T&);
        bool pop();
        int size() const;
        T& front() const;
};

template <typename T>
bool QueueTP<T>::isempty() const{
    if(top_ == 0) return true;
    else return false;
}

template <typename T>
bool QueueTP<T>::isFull() const{
    if(top_ == size_) return true;
    else return false;
}

template <typename T>
bool QueueTP<T>::push(const T& item){
    if(isFull()) return false;
    else{
        items_[top_++] = item;
        return true;
    }
}

template <typename T>
bool QueueTP<T>::pop(){
    if(isempty()) return false;
    else{
        top_ --;
        return true;
    }
}

template <typename T>
int QueueTP<T>::size() const{
    return top_;
}

template <typename T>
T& QueueTP<T>::front() const{
    return items_[top_ - 1];
}

int main(){
    std::shared_ptr<Worker> p_worker = std::make_shared<Worker>("fangsen", 1234);
    p_worker->Show();
    QueueTP<std::shared_ptr<Worker>> que(10);
    std::cout << "Que is empty: " << que.isempty() << std::endl;
    std::cout << "push sucessfully: " << que.push(p_worker) << std::endl;
    std::shared_ptr<Worker> p_front = que.front();
    p_front->Show();
    return 0;
}
