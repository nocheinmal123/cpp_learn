#include <iostream>
#include <string.h>
#include <string>
#include <memory>

namespace QUEUE{
    template<typename Type>
    class Node;
    template<typename Type>
    class Queue;
    template<typename Type>
    std::ostream& operator<<(std::ostream& out, const Node<Type>& node);

    template<typename Type>
    class Node{
        private:
            Type data;
            std::shared_ptr<Node<Type>> nxt;
            template <typename Q>
            friend class Queue;
        public:
            Node(Type _data);
            Node();
            ~Node(){}
            void addData(const Type& _data);
            friend std::ostream& operator<< <>(std::ostream& out, const Node<Type>& node);
    };

    template<typename Type>
    Node<Type>::Node(Type _data){
        this->data = _data;
        nxt = nullptr;
    }

    template<typename Type>
    Node<Type>::Node(){
        nxt = nullptr;
    }

    template<typename Type>
    void Node<Type>::addData(const Type& _data){
        this->data = _data;
    }

    template<typename Type>
    std::ostream& operator<<(std::ostream& out, const Node<Type>& node){
        out << node.data;
        return out;
    }

    template<typename Type>
    class Queue{
        private:
            const int Q_SIZE;
            int _size;
            std::shared_ptr<Node<Type>> _front;
            std::shared_ptr<Node<Type>> _rear;
        public:
            Queue(int _length);
            Queue();
            ~Queue(){}
            bool isempty() const;
            bool isfull() const;
            bool push(const Type& _item);
            bool pop();
            const Node<Type>& front() const;
            int size() const;
    };

    template<typename Type>
    Queue<Type>::Queue(int _length):Q_SIZE(_length){
        _size = 0;
        _front = std::make_shared<Node<Type>>();
        _rear = std::make_shared<Node<Type>>();
    }

    template<typename Type>
    Queue<Type>::Queue():Q_SIZE(10){
        _size = 10;
        _front = std::make_shared<Node<Type>>();
        _rear = std::make_shared<Node<Type>>();
    }

    template<typename Type>
    bool Queue<Type>::isempty() const{
        return _size == 0;
    }

    template<typename Type>
    bool Queue<Type>::isfull() const{
        return _size == Q_SIZE;
    }

    template<typename Type>
    bool Queue<Type>::push(const Type& _item){
        if(_size < Q_SIZE){
            if(_size == 0){
                _rear = std::make_shared<Node<Type>>(_item);
                _front->nxt = _rear;
            }
            else{
               _rear->nxt = std::make_shared<Node<Type>>(_item);
               _rear = _rear->nxt; 
            }
            _size++;
            return true;
        }
        else return false;
    }

    template<typename Type>
    bool Queue<Type>::pop(){
        if(_size){
            _front->nxt = (_front->nxt)->nxt;
            _size--;
            return true;
        }
        else return false;
    }

    template<typename Type>
    int Queue<Type>::size() const{
        return _size;
    }

    template<typename Type>
    const Node<Type>& Queue<Type>::front() const{
       return *(_front->nxt); 
    }
}