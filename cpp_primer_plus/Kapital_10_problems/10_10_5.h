#include <iostream>
#include <string>
#include <string.h>

class customer;

template <typename Type>
class Stack{
    private:
        int index_top;
        int len;
        Type* elements;
    public:
        Stack(const int _len);
        ~Stack();
        bool push(Type item);
        bool pop();
        const Type& top() const;
        int size() const;
        bool isFull() const;
        bool isEmpty() const;
};

template <typename Type>
Stack<Type>::Stack(const int _len){
    index_top = 0;
    len = _len;
    elements = new Type[len];
}

template <typename Type>
Stack<Type>::~Stack(){
    // std::cout << "Stack class decon called.\n";
    delete[] elements;
}

template <typename Type>
bool Stack<Type>::push(Type item){
    if(index_top < len){
        *(elements + index_top) = item;
        index_top++;
        return true;
    }
    return false;
}

template <typename Type>
bool Stack<Type>::pop(){
    if(index_top > 0){
        index_top--;
        return true;
    }
    return false;
}

template <typename Type>
const Type& Stack<Type>::top() const{
    if(index_top){
        return *(elements + index_top - 1);
    }
}

template <typename Type>
int Stack<Type>::size() const{
    return index_top;
}

template <typename Type>
bool Stack<Type>::isEmpty() const{
    if(index_top == 0) return true;
    else return false;
}

template<typename Type>
bool Stack<Type>::isFull() const{
    if(index_top == len) return true;
    return false;
}

class customer{
    private:
        char *fullname;
        double payment;
        static double sum_payment;
    public:
        customer(const char* _fullname, double _payment);
        customer(const customer& _customer);
        customer();
        ~customer();
        customer& operator=(const customer& _src);
        const char* getFullname() const;
        const double getPayment() const;
};