#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

/*
左值，就是能在赋值语句等号左侧的内容（它得代表一个内存地址！），右值就是不能作为左值值。C++中，一个值，要么是左值
要么是右值，不可能两者都是，但是
i = i + 1;
这条语句表示一个左值有时可以被当作右值使用，在这里，i在赋值语句等号的左侧时，用的是这个对象的地址，这时这个对象有一种左值属性
当i出现在等号右侧上的时候，用的是他的值，这时这个对象有一种左值属性

临时对象是一个普通的对象，只是由于它并未提供对象名，同时也不像堆对象（无名对象）一样提供了对象的指针
（即知道对象的地址），所以一般只用来作右值，但这并不说明没有左值属性
*/


int main(){

    // lvalue ref
    int a = 1;
    int &b{a};
                        // int& c = 1; wrong, c必须绑定到左值
    const int& c = 1;   //可以，常引用可以绑定到右值  <==> int tempvalue = 1;
                        //                             const int&c = tempvalue;  
        
    // rvalue ref
    int&& refrightvalue = 3; 

    // Comparation
    std::string strtest{"This is a test"};
    std::string& r1 = strtest;
    // std::string& r2 = {"This is also a test"};       //不可以，左值引用不能绑定到临时变量上
    const std::string& r3 = {"This is also a test"};    //可以，创建一个临时变量，绑定到左值r3上面
                                                        //const引用不但可以绑定到右值，还可以执行到string的隐式转换，并将所得到的值放到string的临时变量中
                                                        //std::string&& r4 = strtest; 不可以，右值引用不能绑定到左值上去
    std::string&& r5 = {"XXXXX"};                       //可以，右值引用绑定到一个临时变量上去
    int i = 10;
    int&ri = i;
    // int&& ri2 = i;           不可以，右值引用不能绑定到一个左值上去
    // int& ri3 = i * 100;      不可以，左值引用不能绑定到右值，i*100返回的是一个右值
    const int& ri4 = i * 100;   //可以，常引用可以绑定到右值上
    int&& ri5 = i * 1000;       // 可以，右值引用绑定右值，乘法结果是个右值

    ++i;            //返回的是左值，因为++i表示直接给i加上1，再返回i本身，因为i是变量，可以被赋值，所以是左值
    (++i) = 20;     //可以这么做
    i++;            //返回的是右值，i++先产生了一个临时变量来保存i的值用于使用目的，再给i加上1，接着返回临时变量，
                    //之后系统再释放这个变量，因为返回的是临时变量，所以返回值是右值
                    //(i++) = 20; 错误
    int&& r1 = i++; //
    // int& r2 = i++;
    int& r3 = ++i;
    // int&& r4 = ++i; 不可以，右值引用绑定右值
    
    /*
    1.  上述int&& r1绑定到了右值，但是r1本身是个左值
        int&r5 = r1;成立
    2.  所有变量都要看成左值
    3.  任何函数里面的形参都是左值，因为他们都是变量
    4.  临时对象都是右值
    */
    return 0;
}