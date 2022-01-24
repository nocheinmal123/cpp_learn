#include <iostream>
#include <string>
#include <string.h>

class Time{
    private:
        int hours;
        int minutes;
    public:
        Time();
        Time(int h, int m = 0);
        Time(Time&& t){
            std::cout << "move copy con called.\n";
            this->hours = t.hours;
            this->minutes = t.minutes;
        }
        Time(const Time& t){
            this->hours = t.hours;
            this->minutes = t.minutes;
        }
        void AddMin(int m);
        void AddHr(int h);
        void Reset(int h = 0, int m = 0);
        Time Sum(const Time& t) const;
        Time operator+(const Time& t) const;
        Time operator-(const Time& t) const;
        Time operator*(int mult) const;
        friend Time operator*(int r, const Time& t);
        Time& operator++();             // reload of "++a", the return value is a ref
        Time operator++(int);           // reload of "a++", the return value is just a, but with "int" as param of func
        // 注意，int 在 括号内是为了向编译器说明这是一个后缀形式，而不是表示整数
        friend Time& operator--(Time& t);
        friend Time operator--(Time& t, int);
        Time& operator=(const Time& t){
            this->minutes = t.minutes;
            this->hours = t.hours;
            return *this;
        }
        bool operator <=(const Time& t){
            if(this->hours != t.hours) return this->hours <= t.hours;
            else return this->minutes <= t.minutes;
        }
        friend std::ostream& operator<<(std::ostream& out, const Time& t);
        friend std::istream& operator>>(std::istream& in, Time& t);
        // cout 是从左往右结合的，因此，要想实现 cout << x << y 这种连续输出
        // 必须使用返回是引用的形式
        // 首先，cout << x 会返回一个ostream类型的对象的引用，然后再调用友元函数
        // 返回一个 ostream类型的对象的引用
        void Show() const;
};