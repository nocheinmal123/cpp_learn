#include <iostream>
#include <string>
#include <string.h>


/**
 * 枚举作为非类型模板参数
 * 如果是非类型模板参数，那么特化指的就是该类型，不同的取值
 */

enum class Type {
    TypeOne,
    TypeTwo,
    TypeThree
};

template <Type type_>
void func() {
    std::cout << "normal version" << std::endl;
}

template <>
void func<Type::TypeOne>() {
    std::cout << "specilization " << int(Type::TypeOne) << std::endl;
}

template <>
void func<Type::TypeThree>() {
    std::cout << "another version " << int(Type::TypeThree) << std::endl;
}

template <int T>
void func_int() {
    std::cout << "allgemein version" << std::endl;
}

template <>
void func_int<10>() {
    std::cout << "10 version" << std::endl;
}


int main() {
    func<Type::TypeOne>();
    func<Type::TypeTwo>();
    func<Type::TypeThree>();
    func_int<20>();
    func_int<10>();
    return 0;
}