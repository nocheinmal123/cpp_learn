#include "11_mytime0.h"

Time::Time()
{
    hours = minutes = 0;
}

Time::Time(int _h, int _m) : hours(_h), minutes(_m)
{
    hours += minutes / 60;
    minutes %= 60;
}

void Time::AddMin(int m)
{
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
}

void Time::AddHr(int h)
{
    hours += h;
}

Time Time::Sum(const Time &t) const
{
    // 不要返回局部变量或者临时对象的引用。函数执行完毕后
    // 局部变量和临时对象都将消失，引用将指向不存在的数据
    Time sum;
    sum.minutes = this->minutes + t.minutes;
    sum.hours = this->hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

Time Time::operator+(const Time &t) const
{
    Time sum;
    sum.minutes = this->minutes + t.minutes;
    sum.hours = this->hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

Time Time::operator-(const Time &t) const
{
    Time res;
    int tot_1 = t.minutes + 60 * t.hours;
    int tot_2 = minutes + 60 * hours;
    res.minutes = (tot_2 - tot_1) % 60;
    res.hours = (tot_2 - tot_1) / 60;
    return res;
}

Time Time::operator*(int mult) const
{
    Time res;
    int tot_min = hours * mult * 60 + minutes * mult;
    res.hours = tot_min / 60;
    res.minutes = tot_min % 60;
    return res;
}

Time operator*(int r, const Time& t){
    Time res(t);
    int tot_min = t.minutes * r + t.hours * r * 60;
    res.minutes = tot_min %60;
    res.hours = tot_min / 60;
    return res;
}

Time &Time::operator++()
{
    int tot_min = this->minutes + 60 * this->hours + 1;
    this->minutes = tot_min % 60;
    this->hours = tot_min / 60;
    return *this;
}

Time Time::operator++(int){
    Time res(*this);
    int tot_min = this->minutes + 60 * this->hours + 1;
    this->minutes = tot_min % 60;
    this->hours = tot_min / 60;
    return res;
}

Time& operator--(Time& t){
    int tot_min = t.minutes + 60 * t.hours - 1;
    t.minutes = tot_min % 60;
    t.hours = tot_min / 60;
    return t;
}

Time operator--(Time& t, int){
    Time res(t);
     int tot_min = t.minutes + 60 * t.hours - 1;
    t.minutes = tot_min % 60;
    t.hours = tot_min / 60;
    return res;
}

std::ostream& operator<<(std::ostream& out, const Time& t){
    out << t.hours << ", " << t.minutes;
    return out;
}

std::istream& operator>>(std::istream& in, Time& t){
    std::cout << "please enter hour and minute:" << std::endl;
    in >> t.hours >> t.minutes;
    return in;
}

void Time::Show() const
{
    std::cout << hours << "hours, " << minutes << " minutes.\n";
}