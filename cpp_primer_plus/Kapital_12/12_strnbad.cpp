#include <string.h>
#include "12_strngbad.h"

int StringBad::num_strings = 0;

StringBad::StringBad(const char* s){
    len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
    num_strings++;
    std::cout << num_strings << ": \"" << str << "\" object created\n";
}

StringBad::StringBad(){
    len = 0;
    str = new char[1];
    // str = new char;这种写法和析构函数不兼容，因为析构函数是delete[] str
    str[0] = 0; // sets str to the null pointer
}

StringBad::StringBad(const StringBad& src){
    len = strlen(src.str);
    str = new char[len + 1];
    strcpy(str, src.str);
    num_strings++;
    std::cout << "copy con called.\n";
}

StringBad::StringBad(StringBad&& src){
    len = strlen(src.str);
    str = new char[len + 1];
    strcpy(str, src.str);
    num_strings++;
    src.str = nullptr;
    std::cout << "move copy con called.\n";
}

StringBad& StringBad::operator=(const StringBad& src){
    if(this == &src) return *this;
    delete[] str;       //free old string, 因为是赋值运算符，所以*this一定2已经有
    // 指向的对象了，所以str肯定指向了某个内存，需要先将其释放，因为稍后要把一个新字符的
    // 地址写给str
    len = src.len;
    str = new char[len + 1];
    strcpy(str, src.str);
    return *this;
}

StringBad& StringBad::operator=(StringBad&& src){
    if(this == &src) return *this;
    len = src.len;
    str = new char[len + 1];
    strcpy(str, src.str);
    delete[] src.str;
    src.str = nullptr;
    return *this;
}

StringBad& StringBad::operator=(const char* s){
    delete[] str;
    len = strlen(str);
    str = new char[len + 1];
    strcpy(str, s);
    return *this;
}

StringBad::~StringBad(){
    // std::cout << "decon called.\n";
    num_strings--;
    delete[] str;
}

std::ostream& operator<<(std::ostream& out, const StringBad& src){
    out << src.str;
    return out;
}

std::istream& operator>>(std::istream& in, StringBad& src){
    in >> src.str;
    return in;
}

bool StringBad::operator<(const StringBad& src){
    if(strcmp(this->str, src.str) < 0) return true;
    else return false;
}

bool StringBad::operator>(const StringBad& src){
    if(strcmp(this->str, src.str) > 0) return true;
    else return false;
    // 利用已经定义好的 < 来定义大于号，对于内联函数来说，是个很好的选择
}

bool StringBad::operator==(const StringBad& src){
    return (strcmp(this->str, src.str) == 0);
}

char& StringBad::operator[](int index){
    std::cout << "normal overload [] called.\n";
    return *(str + index);
}

const char& StringBad::operator[](int index) const{
    std::cout << "const overload [] called.\n";
    return *(str + index);
}

// 静态成员函数，只能访问静态成员变量，比如num_strings
int StringBad::HowMany(){
    return num_strings;
}