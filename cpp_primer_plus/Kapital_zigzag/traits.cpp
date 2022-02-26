#include <iostream>
#include <string>
#include <string.h>

template <typename T>
class Sample {
    public:
        typedef T type_;
        Sample() {};
        ~Sample() {};
};

template <typename T_>
void func(T_& Arg) {
    std::cout << "normal" << std::endl;
}

template <>
void func(Sample<int>& Arg) {
    std::cout << "int" << std::endl;
}

template <>
void func(Sample<double>& Arg) {
    std::cout << "double" << std::endl;
}

template <typename T_>
void _func(T_& Arg) {
    func(Arg);
}

template <typename T_>
struct Type_Traits {
    typedef typename T_::type_ type_;
};

template <>
struct Type_Traits<int> {
    typedef int type_;
};

template <>
struct Type_Traits<double> {
    typedef double type_;
};

template <>
struct Type_Traits<char> {
    typedef char type_;
};

template <typename T>
void funcX(T& Arg, int) {
    std::cout << "int" << std::endl;
}

template <typename T>
void funcX(T& Arg, double) {
    std::cout << "double" << std::endl;
}

template <typename T>
void funcX(T& Arg, char) {
    std::cout << "char" << std::endl;
}

template <typename T>
void _funcX(T& Arg) {
    typename Type_Traits<T>::type_ Tag_;
    funcX(Arg, Tag_);
}


int main() {
    Sample<char> s1;
    Sample<int> s2;
    Sample<double> s3;
    // _func(s1);
    // _func(s2);
    // _func(s3);

    int a;
    double b;
    char c;
    _funcX(a);
    _funcX(s2);
    _funcX(s3);
    _funcX(b);
    _funcX(c);
    _funcX(s1);
    return 0;
}