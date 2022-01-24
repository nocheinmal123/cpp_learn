#include <string.h>
#include <string>
#include <valarray>
#include <iostream>

class Student{
    private:
        using ArrayDb = std::valarray<double>;
        std::string name;
        ArrayDb scores;
        std::ostream& arr_out(std::ostream&) const;
    public: 
        // 初始化顺序是元素被声明的顺序，而不是在初始化列表中的顺序
        Student():name("Null Student"),scores(){}
        explicit Student(const std::string s):name(s), scores(){}
        explicit Student(int n):name("NUlly"), scores(n){}
        Student(const std::string& s, int n):name(s), scores(n){}
        Student(const std::string& s, const ArrayDb& a):name(s), scores(a){}
        Student(const char* str, const double* pd, int n):name(str), scores(pd, n){}
        ~Student(){}
        double Average() const;
        const std::string& Name() const;
        double& operator[](int index);
        double operator[](int index) const;
        friend std::istream& operator>>(std::istream&, Student&);
        friend std::ostream& operator<<(std::ostream&, const Student&);
};