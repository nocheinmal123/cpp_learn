#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
/*
声明区域 declaration region 和
潜在作用域 potential scope
delcaration region:
在函数外声明全局变量，对于这种变量，声明区域为所在的文件；对于函数
中的声明的变量，声明区域为其声明所在的代码块
potential scope:
变量的潜在作用域从声明点开始，到其声明区域的结尾。因此潜在作用域比
声明区域小，因为变量必须在定义后才能使用

命名空间 namespace:
实际上是一种新的声明区域，通过这个新的声明区域来创建命名的名称空间。
这样做的目的之一是提供一个声明名称的区域
命名空间可以是全局的，也可以位于另外一个命名空间中，但不能位于代码
块中。
*/
/*
在9_1_1.cpp和9_1_2.cpp中，讲述的是using声明，现在我们再看看using
编译指令
using编译指令:
using namesapce XXXX
using声明：
using Jill::fetch  // a using declaration
*/

namespace Jill{
    double bucket(double n);
    double fetch;
    struct Hill{};
}

char fetch;             //global namespace

namespace elements{
    namespace fire{
        int flame;
    }
    double w;
}

namespace myth{
    using Jill::fetch;
    using namespace elements;
    using std::cin;
    using std::cout;
}

void func(){
    namespace simple = myth::fire;
}

int main(){
    using namespace Jill;       //using编译指令,import all namespace names
    Hill Thrill;
    double water = bucket(2);
    double fetch;               //not an error; hides Jill::fetch
    std::cin >> fetch;          //read a value into the local fetch
    std::cin >> ::fetch;        //read a value into global fetch
    std::cin >> Jill::fetch;    //read a value into Jill::fetch    

    std::cin >> myth::fetch;    //fetch is now is namespace myth
    std::cin >> Jill::fetch;    //fetch exists in namesapce Jill
    using namespace myth;
    cin >> w;
    namespace MF = elements::fire;      //to simplify the using of namespace
    using MF::flame;
    return 0;
}

/*
总结：
1.假设命名空间和声明区域定义了相同的名称，如果试图使用using声明将名称空间
的名称导入该声明区域，则这两个名称会发生冲突，从而出错。但是如果使用using
编译命令，将该名称空间的各个名称导入该声明区域，则局部版本将隐藏名称空间版本
2.using编译指令具有包含关系，A op B && B op C => A op C
*/