#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <iostream>

// 2.约束模板友元函数
// 首先需要在类的定义前面声明每个模板函数
template<typename Type>
void counts();

template<typename Type>
void report(Type&);


template<typename Type>
class HasFriend{
    private:
        Type item;
        static int ct;
    public:
        HasFriend(const Type& _item):item(_item){
            ct ++;
        }
        ~HasFriend(){
            ct--;
        }
        friend void counts<Type>(); //必须要用Type标注，因为没有模板类作为参数，没有Type得话
        // 编译器会不知道实例化成哪一种
        friend void report<>(HasFriend<Type>&);
};

template<typename Type>
int HasFriend<Type>::ct = 0;

// 友元函数和模板类绑定，只能访问相同类型的模板类的成员变量
template <typename Type>
void counts(){
    std::cout << "template size: " << sizeof(HasFriend<Type>) << "; ";
    std::cout << "tempalte counts(): " << HasFriend<Type>::ct << std::endl;
}

template <typename Type>
void report(Type& hf){
    std::cout << "item = " << hf.item << std::endl;
}

int main(){
    counts<int>();
    HasFriend<int> hf1(12);
    HasFriend<int> hf2(11);
    HasFriend<double> hf3(56.7);
    report(hf1);
    report(hf2);
    report(hf3);
    counts<int>();
    counts<double>();
    return 0;
}