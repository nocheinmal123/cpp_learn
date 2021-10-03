#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
/*
weak_ptr可以理解成用来监视shared_ptr的生命周期用的，是一种对shared_ptr的扩充，
他绑定到shared_ptr上面不会增加shared_ptr引用对象的引用计数，而当shared_ptr指向的
对象需要释时，不会考虑是否有weak_ptr绑定到他上面
*/

int main(){
    auto p_shared = std::make_shared<int>(100);
    std::weak_ptr<int> p_weak_1(p_shared);
    std::weak_ptr<int> p_weak_2;
    p_weak_2 = p_weak_1;
    // 因为weak_ptr所绑定的对象有可能已经不存在了，所以用来直接访问对象，要用lock成员函数
    // 如果对象存在，那么返回一个指向该对象的shared_ptr，当然原shared_ptr引用计数会+1
    // 如果不存在，则返回空的shared_ptr
    auto p_shared_1 = std::make_shared<int>(77);
    std::weak_ptr<int> p_weak_3(p_shared_1);
    auto p_shared_2 = p_weak_3.lock();
    if(p_shared_2 != nullptr) std::cout<<"p_shared_2 is not null"<<std::endl;
    else std::cout<<"p_shared_ptr is null"<<std::endl;
    p_shared_1.reset();     //p_shared_1进行reset
    p_shared_2.reset();     //p_shared_2进行reset
    std::cout<<p_shared_1.use_count()<<std::endl;
    std::cout<<p_shared_2.use_count()<<std::endl;
    auto p_shared_3 = p_weak_3.lock();
    if(p_shared_3 != nullptr) std::cout<<"p_shared_3 is not null"<<std::endl;
    else std::cout<<"p_shared_ptr is null"<<std::endl;

   
    return 0;
}