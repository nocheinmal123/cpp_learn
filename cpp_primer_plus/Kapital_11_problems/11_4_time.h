#include <string>
#include <string.h>
#include <iostream>

namespace TIME{
    class Time{
        private:
            int hours;
            int minutes;
            char* local;
        public:
            explicit Time(int _h , int _m = 0, const char* _local = "Berlin");
            Time(const Time& src);
            Time(Time&& src);
            Time& operator=(const Time& src);
            Time& operator=(Time&& src);
            friend Time operator+(const Time& a, const Time& b);
            friend Time operator+(int r, const Time& src);
            friend Time operator-(const Time& a, const Time& b);
            friend Time operator*(int mult, const Time& src);
            friend Time& operator++(Time& src);
            friend Time operator++(Time& src, int);
            friend Time& operator--(Time& src);
            friend Time operator--(Time& src, int);
            friend std::ostream& operator<<(std::ostream& out, const Time& src);
            friend std::istream& operator>>(std::istream& in, Time& src);
            char& operator[](int index);
    };
}