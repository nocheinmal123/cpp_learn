#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
// malloc和new的区别
// new：可以针对堆所分配的内存进行初始化和释放（构造函数和析构函数）
// malloc：只是在内存中寻找一片指定大小的空间，然后将这个空间的首地址赋值给一个指针变量
/*
new做了两件事情:        1.分配内存 2.调用构造函数进行初始化
delete也做了两件事情:   1.调用析构函数 2.释放内存
*/

class A{
    private:
        int k;
    public:
        A(int _k = 0):k(_k){
            std::cout<<"A con called "<<k<<std::endl;
        }
        ~A(){
            std::cout<<"A decon called "<<k<<std::endl;
        }
};

std::shared_ptr<int> func(int value){
    return std::shared_ptr<int>(new int(value));        //函数调用需要写成这种形式
}

void func1(std::shared_ptr<A> tmp){                     //智能指针作为实参向函数里面传递
    std::cout<<"in the func1, count = "<<tmp.use_count()<<std::endl;
    return;
}

std::shared_ptr<A> func2(std::shared_ptr<A>& tmp){      //引用作为实参向函数传递
    return tmp;                                         //作为函数返回值
}

int main(){
    int* p1 = new int(100);                     //不delete，内存泄漏了4个字节，正常情况
    int* p2 = new int[2];                       //不释放，内存泄漏了8个字节
    int class_size = sizeof(A);                 //1，即使类里面没有成员变量，一个类的对象肯定有地址，一个内存地址至少保存了一个字节
    A* pa1 = new A(1);                          //不delete，内存泄漏1个字节
    A* pa2[2] = {new A(2),new A(3)};            //泄露了6个字节
    delete p1; delete p2; delete pa1; delete pa2[0]; delete pa2[1];
    // 针对非内置类型，C++在new的时候专门多分配了4个字节用来保存数组的大小，所以是泄露了6个字节
    // int* p2 = new int[2]是内置类型，没有额外的空间来保存大小，所以就是泄露了8个字节，否则就是12个了
    // delete []p2 <==> delete p2 其实是一样的，后一种不会造成内存泄露
    /*
    对于内置类型来说，delete的时候不存在调用析构函数，new的时候系统也并没有多分配4个字节
    所以得出结论：
        如果是用new[]来分配内存，但是用 delete（而不是delete[]）来释放内存，那么这个对象要么是内置类型，
        要么就没有自定义的析构函数
    把类A的析构函数注释掉，那么 delete pa2和delete []pa2是一样的的，但是如果有了自定义的析构函数
    那么new[]和delete[]要一起用
    */

    //****************************智能指针初始化**********************
    std::shared_ptr<A> p(new A(4));
    std::shared_ptr<int> p_int(new int(100));
    // std::shared_ptr<A> p2 = new A(); 错误，不能采用隐式转换
    // 最好采用如下的make_share方式进行初始化，make_share<类型名>(类型某个构造函数对应的参数列表)
    std::shared_ptr<A> p_A = std::make_shared<A>(10);
    p_A = std::make_shared<A>(7);
    std::cout<<"--------------------"<<std::endl;
    p_A.reset();
    std::cout<<"--------------------"<<std::endl;
    p.reset();
    std::cout<<"--------------------"<<std::endl;
    //***************************************************************


    //*****************shared_ptr引用计数的增加减少*********************
    std::shared_ptr<A> p_1 = std::make_shared<A>(90);
    auto p_2 = p_1;
    std::cout<<"count = "<<p_1.use_count()<<std::endl;
    func1(p_1);                                 // 指针的引用会先增加1，再减少1
                                                // 因为函数里面的局部变量tmp销毁
    func2(p_1);                                 // 如果没有接收，那么指针的引用不会增加
    std::cout<<"count = "<<p_1.use_count()<<std::endl;
    std::shared_ptr<A> p_3 = func2(p_1);        // 被p_3接收函数返回值，指针引用增加1
    std::cout<<"count = "<<p_1.use_count()<<std::endl;

    p_2 = std::make_shared<A>(89);              // p_1所托管的指针的引用减少1，此时这新产生的指针的引用计数增加1
    //**************************************************************


    //***********************shared_ptr常用惭怍**********************
    // 1. use_count成员函数
    // 2. unique成员函数，用来判断是否该智能指针独占某个指向的对象，
    // 如果只有一个智能指针指向某个对象，返回true否则返回false
    if(p_2.unique()) std::cout<<"unique"<<std::endl;
    else std::cout<<"multi"<<std::endl;
    // 3. reset成员函数
    /*
    reset不带参数
    如果p_2是唯一指向该对象的指针，则将p_2置空，
    否则不释放p_2指向的对象，将p_2置空，但是指向该对象的引用计数会减少1
    */
    p_2.reset();
    if(p_2 == nullptr) std::cout<<"p_2 is now null"<<std::endl;
    else std::cout<<"p_2 is not null"<<std::endl;

    // 注意下面一个例子
    std::shared_ptr<int> p4(new int(100));
    auto p5 = p4;
    std::cout << "p1.count = " << p4.use_count() << std::endl;      //输出2
    std::cout << "p2.count = " << p5.use_count() << std::endl;      //输出2
    p4.reset();
    std::cout << "p1.count = " << p4.use_count() << std::endl;      //输出0
    std::cout << "p2.count = " << p5.use_count() << std::endl;      //输出1
    //为什么reset过后，p4的use_count是0，而不是1呢，因为reset会将p4置空，p4将不再
    // 指向之前的内存，所有这时的p_4.use_count无法获取到之前那个内存的引用计数了
    // 所以变成0了
    /*
    reset带参数
    如果p_2是唯一指向该对象的指针，则将p_2绑定的对象释放，再将p_2指向新内存
    如果p_2不是唯一的，先释放原来的，再指向新的，see Kapital_10
    */
    std::shared_ptr<A> pi(new A(177));
    auto pi2(pi);
    pi.reset();
    if(pi2.unique()) std::cout<<"pi2 is unique"<<std::endl;
    else std::cout<<"not unique"<<std::endl;

    // 4. 解引用*p，获得p指向的对象
    std::shared_ptr<int> p_buf(new int(12345));
    char buf[1024];
    sprintf(buf,"%d",*p_buf);
    std::cout<<buf<<std::endl;

    // 5. get函数，返回p中保存的裸指针，如果智能指针已经不再绑定这个裸指针了，返回值无效
    int* p_get = p_buf.get();           // 不要delete，否则后果难以预料
    // 6. swap函数，交换两个只能指针指向的对象，因为是交换，所以引用计数不发生改变
    std::shared_ptr<std::string> ps1(new std::string("fagnsen"));
    std::shared_ptr<std::string> ps2(new std::string("yilin")); 
    std::swap(ps1,ps2);
    ps1.swap(ps2);                     // 也可以
    
    // 7. = nullptr
    // 将所指的对象的引用计数减1，如果引用计数变为0，则释放智能指针所指向的对象
    // 再将智能指针置空
    ps1 = nullptr; ps2 = nullptr;

    // 8. 智能指针名字作为判断条件
    if(!ps2) std::cout<<"ps2 points dosen't point at sth"<<std::endl;
    if(p_buf) std::cout<<"p_buf 指向一个对象"<<std::endl;
    //*************************************************************

    
    return 0;
}