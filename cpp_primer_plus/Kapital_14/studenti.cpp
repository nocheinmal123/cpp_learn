#include "studenti.h"

// 访问基类的方法，不同于has-a版本，私有继承需要使用::来访问基类的方法
double Student::Average() const{
    if(ArrayDb::size() > 0){
        return ArrayDb::sum() / ArrayDb::size();
    }
    else return 0;
}

// 访问基类对象
// Student的has-a版本实现了Name()的方法，它返回string对象的成员name，但是私有继承时候
// 不存在这个成员name，那么应该怎么访问内部的string对象呢，答案是是使用强制转换
// 因为Student是从string派生而来的，因此可以使用强制换换
const std::string& Student::Name() const{
    return (const std::string&) *this;
}

double& Student::operator[](int index){
    return ArrayDb::operator[](index); //use Array::operator[]()
}

double Student::operator[](int index) const{
    return ArrayDb::operator[](index); //使用::来访问积累的方法
}

std::ostream& Student::arr_out(std::ostream& in) const{
    int lim = ArrayDb::size(); //使用::来访问基类的方法
    int i;
    if(lim > 0){
        for(i=0;i<lim;i++){
            in << ArrayDb::operator[](i) << " ";
            if(i % 5 == 4) in << std::endl;
        }
        if(i % 5 != 0) in << std::endl;
    }
    else in << "Empty array.\n";
    return in;
}

std::istream& operator>>(std::istream& in, Student& stu){
    in >> (std::string&) stu;
    return in;
}

std::ostream& operator<<(std::ostream& src, const Student& stu){
    src << "Scores for " << (const std::string& ) stu << ":\n";
    stu.arr_out(src);
    return src;
}