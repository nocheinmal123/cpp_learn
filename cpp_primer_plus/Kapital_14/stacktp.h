#include <string>
#include <string.h>
#include <iostream>

template<typename Type>
class Stack{
    private:
        Type* items_;
        int top_;
        int size_;
    public:
        explicit Stack(int);
        ~Stack();
        bool isempty();
        bool isfull();
        bool push(const Type&);
        bool push(Type&&);
        const Type& top();
        bool pop();
        int size();
};

template<typename Type>
Stack<Type>::Stack(int len){
    items_ = new Type[len];
    top_ = 0;
    size_ = len;
}

template<typename Type>
Stack<Type>::~Stack(){
    delete[] items_;
}

template<typename Type>
bool Stack<Type>::isempty(){
    if(top_ == 0) return true;
    else return false;
}

template<typename Type>
bool Stack<Type>::isfull(){
    if(top_ == size_) return true;
    else return false;
}

template<typename Type>
bool Stack<Type>::push(const Type& item){
    if(top_ < size_){
        *(items_ + top_) = item;
        top_ ++;
        return true;
    }
    else return false;
}

template<typename Type>
bool Stack<Type>::push(Type&& item){
    std::cout << "move push" << std::endl;
    if(top_ < size_){
        *(items_ + top_) = item;
        top_ ++;
        return true;
    }
    else return false;
}

template<typename Type>
bool Stack<Type>::pop(){
    if(top_ == 0) return false;
    else{
        top_ --;
    }
}

template<typename Type>
const Type& Stack<Type>::top(){
    if(top_) return items_[top_ - 1];
}

template<typename Type>
int Stack<Type>::size(){
    return top_;
}