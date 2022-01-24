#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <iostream>

template<typename Type>
class Stack{
    private:
        Type* ptr; 
        int index_top;
        int MAXN;
    public:
        Stack(int _len);
        ~Stack();
        bool isEmpty() const;
        bool isFull() const;
        bool push(const Type& item);
        bool pop();
        const Type& top() const;
        int size() const;
};

template<typename Type>
Stack<Type>::Stack(int _len){
    ptr = new Type[_len];
    MAXN = _len;
    index_top = 0;
}

template<typename Type>
Stack<Type>::~Stack(){
    delete[] ptr;
}

template<typename Type>
bool Stack<Type>::isEmpty() const{
    return index_top == 0;
}

template<typename Type>
bool Stack<Type>::isFull() const{
    return index_top == MAXN;
}

template<typename Type>
bool Stack<Type>::push(const Type& item){
    if(index_top < MAXN){
        *(ptr+index_top) = item;
        index_top++;
        return true;
    }
    else return false;
}

template<typename Type>
bool Stack<Type>::pop(){
    if(index_top > 0){
        index_top--;
        return true;
    }
    return false;
}

template<typename Type>
const Type& Stack<Type>::top() const{
    return *(ptr + index_top - 1);
}

template<typename Type>
int Stack<Type>::size() const{
    return index_top;
}