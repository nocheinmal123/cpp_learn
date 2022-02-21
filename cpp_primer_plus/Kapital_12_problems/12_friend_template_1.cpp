#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <iostream>

// 1.友元函数的参数是模板类，友元函数本身并不是模板函数
// 并且不使用模板类作为参数，比如这里的counts函数，
// 可以访问任何实例化类型的模板类中的任何成员变量
// 并且，实际上只有一个友元函数，并不会有好几个具体化的友元函数
template<typename Type>
class HasFriend{
    private:  
        Type item;
        // static int ct;
    public:
        static int ct;
        HasFriend(const Type& _item):item(_item){
            ct ++;
        }
        ~HasFriend(){
            ct--;
        }
        friend void counts();
        friend void report(HasFriend<Type>&);
};

// 正常写法就是HasFriend::ct，但是因为是模板类
// 所以HasFriend<Type>是一个类型名字，所以这样表达
// 会产生很多ct，每个类型都有自己的ct，互不影响
template<typename Type>
int HasFriend<Type>::ct = 0;

void counts(){
    std::cout << "int count: " << HasFriend<int>::ct << std::endl;
    std::cout << "double count: " << HasFriend<double>::ct << std::endl;
}

// 由于report函数使用模板类作为参数，因此必须在外面
// 显示地特例化
void report(HasFriend<int>& hf){
    std::cout << hf.item << std::endl;
}

void report(HasFriend<double>& hf){
    std::cout << hf.item << std::endl;
}

int main(){
    counts();
    HasFriend<int> hf1(100);
    counts();

    HasFriend<double> hf2(76.3);
    report(hf1);
    counts();
    report(hf2);

    HasFriend<int> hf3(45);
    report(hf3);
    counts();

    return 0;
}