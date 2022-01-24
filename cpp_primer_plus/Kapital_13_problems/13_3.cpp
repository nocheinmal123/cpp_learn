#include "13_3.h"

int main(){
    baseDMA* bm = new baseDMA("label",0);
    bm->View();
    baseDMA bm_obj("label2",10);
    std::cout <<bm_obj << std::endl;
    baseDMA bm_oj2(bm_obj);
    bm_oj2.View();

    lacksDMA* lm = new lacksDMA("red", "tata",1000);
    lm->View();
    lacksDMA lm_obj("green", "dada", 107);
    std::cout << lm_obj << std::endl;
    lacksDMA lm_obj2(lm_obj);
    lm_obj2.View();

    DMA* dma[2];
    dma[0] = new baseDMA("kkkk",101);
    dma[1] = new lacksDMA("jjjj","ilil",109);
    dma[0]->View();
    dma[1]->View();

    int k = 1;
    /*
    为什么运算符重载返回引用？
    1.用来完成“连续操作”,比如 a = b = c, a += b += c, ++(++k) 而且连续操作会影响自身的值，因此需要传递引用
    用来改变“自身的值”
    2.为了解决多次调用拷贝构造函数和析构函数
    为什么 ++前缀需要使用返回引用，但是++后缀返回的是值呢
    因为++后缀先返回，然后再完成对自身的操作，所以先返回的时候无法返回自身（后面还需要对自身操作），
    所以后缀采用返回值的方式，这也是因此后缀++是右值表达式的原因。后缀++返回的是一个右值，一个临时
    对象
    */
    return 0;
}