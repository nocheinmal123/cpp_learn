#include <iostream>
#include <string>
#include <string.h>

/*
这里的T叫作类型参数，n叫作非类型参数或者表达式参数，表达式参数可以是
整型，枚举，指针，引用，但是不能是浮点等，另外模板代码也不能更改参数
的值，也不能使用参数的地址
*/

template<typename T, int n>
class ArrayTP{
    private:
        T ar[n];
    public:
        ArrayTP() {};
        explicit ArrayTP(const T&);
        virtual T& operator[](int);
        virtual T operator[](int) const;
};

template<typename T, int n>
ArrayTP<T, n>::ArrayTP(const T& v){
    for(int i = 0; i < n; i++){
        ar[i] = v;
    }
}

template<typename T, int n>
T& ArrayTP<T, n>::operator[](int index){
    if(index < 0 || index >= n){
        std::errc << "Error in array limits: " << i << " is out of range.\n";
        std::exit(EXIT_FAILURE)
    }
    return ar[index];
}

template<typename T, int n>
T ArrayTP<T, n>::operator[](int index) const{
    if(index < 0 || index >= n){
        std::errc << "Error in array limits: " << i << " is out of range.\n";
        std::exit(EXIT_FAILURE)
    }
    return ar[index];
}