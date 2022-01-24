#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <iostream>

// 3.非约束模板有元
// 可以同时访问不同类型具体化的模板类
template<typename Type>
class ManyFriend{
    private:
        Type item;
    public:
        ManyFriend(const Type& _item):item(_item){

        }
        template<typename T1, typename T2>
        friend void show(T1&, T2&);
};

template<typename T1, typename T2>
void show(T1& item1, T2& item2){
    std::cout << item1.item << ", " << item2.item << std::endl;
}

int main(){
    ManyFriend<int> hf1(10);
    ManyFriend<int> hf2(12);
    ManyFriend<double> hf3(56.9);
    show(hf1, hf2);
    show(hf1, hf3);
    return 0;
}