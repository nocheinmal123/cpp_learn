#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

int main()
{
    // 1. use_count成员函数，该成员函数获取该弱指针共享对象的其他shared_ptr的数量
    // 或者说是获得当前所观测的shared_ptr所指向对象的引用计数
    std::shared_ptr<int> p_shared_1(new int(17));
    std::weak_ptr<int> p_weak_1(p_shared_1);
    std::cout << "p_weak_1 = " << p_weak_1.use_count() << std::endl;
    auto p_shared_2(p_shared_1);
    std::cout << "p_weak_1 = " << p_weak_1.use_count() << std::endl;

    // 2. expired成员函数，如果该弱指针的use_count为0（表示该弱指针所指向的对象已经不存在），则返回true
    // 否则返回false
    p_shared_1.reset();
    p_shared_2.reset();
    if(p_weak_1.expired()) std::cout<<"p_weak_1 is expired"<<std::endl;
    else std::cout<<"p_weak_1 is NOT expired"<<std::endl;

    // 3. reset成员函数，将该弱引用指针设置为空，不影响shared_ptr的引用计数
    // 但弱引用计数减少1
    std::shared_ptr<int> p_shared_3 = std::make_shared<int>(45);
    std::weak_ptr<int> p_weak_2(p_shared_3);
    std::cout<<"p_weak_2 = "<<p_weak_2.use_count()<<std::endl;
    p_weak_2.reset();
    std::cout<<"p_weak_2 = "<<p_weak_2.use_count()<<std::endl;

    // 4. lock成员函数
    auto p_shared_4 = std::make_shared<int>(78);
    std::weak_ptr<int> p_weak_4(p_shared_4);
    if(!p_weak_4.expired()){
        auto p_shared_5 = p_weak_4.lock();                  //2个强引用，1个弱引用
        if(p_shared_5 != nullptr){
            std::cout<<*(p_shared_5.get())<<std::endl;
            std::cout<<p_shared_5.use_count()<<std::endl;
            std::cout<<p_shared_4.use_count()<<std::endl;
        }
    }
    std::cout<<p_shared_4.use_count()<<std::endl;           //恢复到1个强引用

    // 5. 尺寸问题
    std::cout<<"size shared = "<<sizeof(p_shared_4)<<std::endl;
    std::cout<<"size weak = "<<sizeof(p_weak_4)<<std::endl;
    std::cout<<"size normal pointer = "<<sizeof(p_shared_4.get())<<std::endl;
    /*
    weak指针和shared指针的尺寸是一样的，都是正常指针大小的2倍，里面包含
    1.第一个裸指针指向的的是该智能指针指向的对象
    2.第二个裸指针指向一个很大的数据结构，里面包含所指对象的引用计数，所指对象的弱引用计数，
    自定义的删除器的指针等等 
    */
    return 0;
}