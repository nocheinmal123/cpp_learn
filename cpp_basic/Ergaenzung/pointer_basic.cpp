#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

//********************指针作为函数参数******************************
void func1(int arr1[]){
    std::cout<<"in func1: ";
    std::cout<<sizeof(arr1)/sizeof(int)<<std::endl;         //输出2，arr1是数组指针
}

void func2(int* arr2){
    std::cout<<"in func2: ";
    std::cout<<sizeof(arr2)/sizeof(int)<<std::endl;         //输出2，也是数组指针
}
//***************************************************************



//*********************指针作为函数的返回值**************************
char* strlong(char* str1, char* str2){
    if(strlen(str1) >= strlen(str2)) return str1;
    else return str2;
}

int* func3(){
    int n = 100;
    return &n;      //将局部变量作为返回值
}
//***************************************************************



//*******************空指针NULL和void指针**************************
/*
在stdio.h中，可以找到关于NULL的定义
#define NULL ((void*)0)
表示强制把数值0转换成void*类型，从整体上看，NULL指向了地址为0的内存，在操作
系统中有一段叫最低地址区域这个区域不保存数据，也不能被用户访问，
NULL指向的就是这个区域内的任何一个地址
*/
void func4(){
    char* p = NULL;             //对没有初始化的指针赋值NULL
}

void func5(){
    // void指针，void*表示一个有效指针，他指向实实在在的数据，只是数据的类型尚未确定，
    // 在后续使用中，一般需要强制转换
    // 分配可以保存30个字符的内存，并把返回的指针转换为char*
    char* p =(char*)malloc(sizeof(char)*30);     
    scanf("%s",p);
    printf("str = %s\n",p);   
}
//**************************************************************



//*********************二维数组指针*******************************
void func6(){
    int a[3][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,1}};
    int (*p)[4] = a;
    // p指向的数据类型是int[4],p+1前进了16个字节，p-1后退了16个字节
    // 也就是说p+1指向了数组a的下一行，p-1指向了数组a的前一行
    std::cout<<*(p+1)<<std::endl;
}
//**************************************************************



//*********************函数指针**********************************
/*
一个函数总是占用一段连续的内存区域，函数名在表达式中有时也会被转换成该函数所在
内存区域的首地址，这个首地址（入口地址）可以被赋予一个指针变量，通过该指针可以
找到这个函数
returnType (*pointerName)(paramlist of func)
*/

int Max(int a,int b){
    return std::max(a,b);
}

int Max(){
    return 10;
}

void func7(){
    int x,y;
    int (*p_func)(int,int) = Max;       //(*p_func)括号不可缺,函数指针可以看成是个"数组指针"，          
                                        // 所以用法也很相似
    int (*p_func2)() = Max;             //()也不可缺，即使是无参函数
    scanf("%d %d",&x,&y);
    printf("%d\n",p_func(x,y));      //也可以写成(*p_func)(x,y),但是为了和“数组指针”相似，方便记忆
                                     //还是写成这种不带*号的 
    printf("%d\n",p_func2());        //()也不可缺，否则无法区分是函数指针还是普通指针
}
//*************************************************************


int main(){
    int arr[5] = {0,12,7,-1,3};
    int* p_arr = arr;
    std::cout<<"size of the pointer p_arr = "<<sizeof(p_arr)<<std::endl;
    // 指针的大小是固定的，和指针类型无关(不管是int类型，char类型还是别的)，只和机器最小寻址长度有关
    // 同时，要注意，指向数组的指针（在这里是p_arr）和数组不是一个东西，看如下例子

    std::cout<<sizeof(arr)/sizeof(int)<<std::endl;      //输出5，表示数组长度
    std::cout<<sizeof(p_arr)/sizeof(int)<<std::endl;    //输出2，因为机器最小寻址长度是8，int是4
    // 从上面可以看出，p_arr只是个指针，无法从中得出数组的长度，指向数组的指针和数组不太一样
    
    // 但是函数把数组作为实参传递的时候，传递的实际是指针，而不是传递整个数组（开销太大）
    func1(arr);
    func2(arr);

    int* p = arr;
    *p++;       // <==> *(p++)
    *++p;       // <==> *(++p)
    (*p)++;

    /*
    int* p_func3 = func3();
    int n = *p_func3;
    std::cout<<"n = "<<n<<std::endl;        //输出100
    std::cout<<"just saying"<<std::endl;
    std::cout<<"n = "<<n<<std::endl;        //输出-2
    为什么运行那句随便打印之前，还是能达到正确的数据呢，之前所谓的函数运行结束后会销毁局部变量指的并不是
    将局部变量的内存全部抹掉，而是放弃对这些内存的使用权，后面的代码可以随意往这些内存写入东西，在写入之前
    这些内存保存的数据依旧完好，所以能拿到100，随便执行了一句程序，那段内存就可能被重新写入了，拿到的数据
    就不对了
    */

    func5();
    func6();
    func7();
    return 0;
}