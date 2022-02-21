#include <iostream>
#include <string>
#include <string.h>
#include <valarray>

class Student: private std::string, private std::valarray<double>{
    private:
        using ArrayDb = std::valarray<double>;
        std::ostream& arr_out(std::ostream& )const;
    public:
        Student():std::string("Null Student"), ArrayDb(){}
        explicit Student(const std::string& s):std::string(s),ArrayDb(){}
        explicit Student(int n):std::string("Nully"), ArrayDb(n){}
        Student(const std::string& s, int n):std::string(s),ArrayDb(n){}
        Student(const char* str, const double* pd, int n):std::string(str),ArrayDb(pd, n){}
        ~Student(){}
        double Average() const;
        double& operator[](int index);
        double operator[](int index) const;
        const std::string& Name() const;
        
        friend std::istream& operator>>(std::istream&, Student& stu);
        friend std::ostream& operator<<(std::ostream&, const Student& stu);
};
/*
1.初始化基类组件
隐式地继承组件而不是成员对象将影响代码编写规则，因为再也不能使用name和scores来描述对象了，
而必须使用用于公有继承的技术，比如，has-a关系将使用如下构造函数：
Student(const char* str, const double* pd, int n): name(str), scores(pd, n) {}
对于继承类，新版本的构造函数将使用成员初始化列表语法，但是它使用的是类名，而不是成员名来标识构造函数
Student(const char* str, const double* pd, int n): std::string(str), ArrayDb(pd, n) {}

2.访问基类的方法
has-a:
使用.来访问
私有继承关系中，只能在派生类的方法中使用基类的方法：
使用::来访问基类的方法
*/

/*
class base{
    private:
        int n;
    public:
        base(int _n):n(_n){}
        ~base(){}
};

class derived: private base{
    private:
        std::string str;
    public:
        derived(const std::string& _str, int _n):str(_str), base(_n){}
        explicit derived(const std::string& _str):str(_str), base(0){}
        explicit derived(int _n):str("Null"), base(_n){}
        ~derived(){}
};
*/