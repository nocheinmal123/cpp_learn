#include <iostream>
#include <string>
#include <string.h>
/*讲解decltype
decltype类型说明符，它的作用是选择并返回操作数的数据类型，在此过程中，
编译器分析表达式并得到它的类型，却不实际计算表达式的值*/
int getSize();

void func_const(){
    double tempA = 3.0;
    const double ctempA = 5.0;
    const double ctempB = 7.4;
    const double *const cptrTempA = &ctempA;
    // II 与const结合
    /*1. dclTempA推断为const double, 保留了顶层的const，此处与auto不同*/
    decltype(ctempA) dclTempA = 3.5;
    /*2. dclTempA类型为const double,不能对其进行赋值，无法编译*/
    // dclTempA = 10.9;
    /*3. dclTempB推断为const double *const */
    decltype(cptrTempA) dclTempB = &ctempA;
    /*4. 输出为4（32位计算机）和5*/
    std::cout << "sizeof(dclTempB)" << " " << *dclTempB << std::endl;
    /*5. 保留顶层const, 不能修改指针指向的对象，编译不过*/
    // dclTempB = &ctempB;
    /*6. 保留底层const，不能对指针指向的对象进行修改，编译不过*/
    // *dclTempB = 10.04;
}

void func_ref(){
    // III 与引用结合
    int tempA = 0;
    int& refTempA = tempA;
    /*1. dclTempA为引用，绑定到tempA*/
    decltype(refTempA) dclTempA = tempA;
    /*2. dclTempB为引用，必须绑定到变量，编译不过*/
    // decltype(refTempA) dclTempB = 0;
    /*3. dclTempC为引用，必须初始化，编译不过*/
    // decltype(refTempA) dclTempC;
    /*4. 双层括号表示引用，dclTempD为引用，绑定到tempA上面*/
    decltype((tempA)) dclTempD = tempA;

    const int ctempA = 1;
    const int& creftempA = ctempA;
    /*5. dclTempE为常引用，可以绑定到普通变量tempA*/
    decltype(creftempA) dclTempE = tempA;
    /*6. dclTempF为常引用，可以绑定到常量ctempA*/
    decltype(creftempA) dclTempF = ctempA;
    /*7. dclTempG为常引用，可以绑定到临时变量上*/
    decltype(creftempA) dclTempG = 14;
}


void func_ptr(){
    // V. 与指针结合
    int tempA = 2;
    int* ptrTempA = &tempA;
    /*1. 常规使用dclTempA,类型是int*的指针*/
    decltype(ptrTempA) dclTempA;
    /*2. 需要特别注意这个，表达式内容为解引用操作，所以类型是引用，必须进行初始化*/
    decltype(*ptrTempA) dclTempB = tempA;
}

int main(){
    // I 基本用法
    int tempA = 2;
    /*1. dclTempA为int类型*/
    decltype(tempA) dclTempA;
    /*2. dclTempB为int类型，对于getSize()根本没有定义，但是程序可以正常运行
    因为decltype只做分析，不调用getSize*/
    decltype(getSize()) dclTempB;


    /*注意！！！
    变量是一种可以作为赋值语句的特殊表达式，因为赋值语句的返回值是引用，
    所以变量作为表达式的时候类型是引用
    */
    int i = 42;
    int k = 19;
    decltype(i) d; // d的类型是int
    decltype((i)) e = k; // e的类型是int&, 所以必须进行初始化


    /*
    1. auto忽略顶层const(除非是和引用或者指针结合，auto会保留顶层const)，decltype保留顶层const
    2. 对引用操作，auto推断出原有类型，decltype推断出引用
    3. 对解引用操作，auto推断出原有类型，decltype推断出引用
    4. auto推断时候会执行，decltype只做分析
    */
    return 0;
}