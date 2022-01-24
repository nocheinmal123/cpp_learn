#include "11_4_time.h"
namespace TIME{
    Time::Time(int _h, int _m, const char* _local){
        hours = _h;
        minutes = _m;
        int len = strlen(_local);
        local = new char[len + 1];
        strcpy(local, _local);
    }
    Time::Time(const Time& src){
        std::cout << "copy con called.\n";
        hours = src.hours;
        minutes = src.minutes;
        int len = strlen(src.local);
        local = new char[len + 1];
        strcpy(local, src.local);
    }
    Time::Time(Time&& src){
        std::cout << "move copy con called.\n";
        hours = src.hours;
        minutes = src.minutes;
        int len = strlen(src.local);
        local = new char[len + 1];
        strcpy(local, src.local);
        src.local = nullptr;
    }
    Time& Time::operator=(const Time& src){
        hours = src.hours;
        minutes = src.minutes;
        int len = strlen(src.local);
        local = new char[len + 1];
        strcpy(local, src.local);
    }
    Time& Time::operator=(Time&& src){
        hours = src.hours;
        minutes = src.minutes;
        int len = strlen(src.local);
        local = new char[len + 1];
        strcpy(local, src.local);
        src.local = nullptr;
    }
    Time operator+(const Time& a, const Time& b){
        int tot_min = a.minutes + 60*a.hours + b.minutes + 60*b.hours;
        int h = tot_min/60;
        int m = tot_min%60;
        int len = strlen(a.local);
        char* s = new char[len + 1];
        strcpy(s, a.local);
        return Time(h, m, s);
    }
    Time operator+(int r, const Time& src){
        int tot_min = src.minutes + 60*src.hours + r;
        int h = tot_min/60;
        int m = tot_min%60;
        int len = strlen(src.local);
        char* s = new char[len + 1];
        stpcpy(s, src.local);
        return Time(h, m, s);
    }
    Time operator-(const Time& a, const Time& b){
        int tot_min = a.minutes + 60*a.hours - (b.minutes + 60*b.hours);
        int len = strlen(a.local);
        char* s = new char[len + 1];
        strcpy(s, a.local);
        if(tot_min <= 0){
            return Time(0, 0, s);
        }
        else{
            int h = tot_min/60;
            int m = tot_min%60;
            return Time(h, m, s);
        }
    }
    Time operator*(int mult, const Time& src){
        int tot_min = mult*src.minutes + mult*60*src.hours;
        int h = tot_min/60;
        int m = tot_min%60;
        int len = strlen(src.local);
        char* s = new char[len + 1];
        strcpy(s, src.local);
        return Time(h, m, s);
    }
    Time& operator++(Time& src){
        int tot_min = src.minutes + 1 + 60*(src.hours + 1);
        int h = tot_min/60;
        int m = tot_min%60;
        src.minutes = m;
        src.hours = h; 
        return src;
    }
    Time operator++(Time& src, int){
        Time res(const_cast<Time&>(src));
        int tot_min = src.minutes + 1 + 60*(src.hours + 1);
        int h = tot_min/60;
        int m = tot_min%60;
        src.minutes = m;
        src.hours = h;
        return res;
    }
    Time& operator--(Time& src){
        int tot_min = src.minutes - 1 + 60*(src.hours - 1);
        int h = tot_min/60;
        int m = tot_min%60;
        src.minutes = std::max(0, m);
        src.hours = std::max(0, h);
        return src;
    }
    Time operator--(Time& src, int){
        Time res(const_cast<Time&>(src));
        int tot_min = src.minutes - 1 + 60*(src.hours - 1);
        int h = tot_min/60;
        int m = tot_min%60;
        src.minutes = std::max(0, m);
        src.hours = std::max(0, h);
        return res;
    }
    std::ostream& operator<<(std::ostream& out, const Time& src){
        out << "h = " << src.hours << ", m = " << src.minutes <<", local = " << src.local;
        return out;
    }
    std::istream& operator>>(std::istream& in, Time& src){
        std::cout << "Enter hour and minute please:" << std::endl;
        in >> src.hours >> src.minutes;
        return in;
    }
    char& Time::operator[](int index){
        return local[index];
    }
}