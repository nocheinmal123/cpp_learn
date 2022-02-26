#include <iostream>
#include <string>
#include <string.h>
#include <memory>

template <typename T_>
class QueueTP {
    private:
        enum {Q_SIZE = 10};
        class Node {
            public:
                T_ item;
                std::shared_ptr<Node> next;
                Node(constT& i): item(i), next(nullptr) {}
        };
        std::shared_ptr<Node> front;
        std::shared_ptr<Node> rear;
        int items;
        const int qsize;
        QueueTP(const QueueTP& q): qsize(0) {}
        QueueTP& operator=(const QueueTP& q) { return *this;}
    public:
        QueueTP(int qs = Q_SIZE);
        ~QueueTP();
        bool isempty() const {
            return items == 0;
        }
        bool isfull() const {
            return items == qsize;
        }
        int queuecount() const {
            return items;
        }
        bool enqueue(const T_& item);
        bool dequeue();

};

template <typename T_>
QueueTP<T_>::QueueTP(int qs): qsize(qs) {
    front = rear = nullptr;
    items = 0;
}

template <typename T_>
QueueTP<T_>::~QueueTP() {

}

template <typename T_>
bool QueueTP<T_>::enqueue(const T_& item) {
    if (isfull()) return false;
    std::shared_ptr<Node> add = std::make_shared<Node>(item);
    if (front == nullptr)
        front = add;
    else
        rear->next = add;
    rear = add;
    return true;
}

template <typename T_>
bool QueueTP<T_>::dequeue() {
    if (isempty()) return false;
    front = front->next;
    items--;
    if(items == 0) front = rear = nullptr;
    return true;
}