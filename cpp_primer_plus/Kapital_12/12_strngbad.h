#include <iostream>
class StringBad{
    private:
        char* str;
        int len;
        static int num_strings;
    public:
        StringBad(const char* s);
        StringBad();
        StringBad(const StringBad& );
        StringBad(StringBad&&);
        StringBad& operator=(const StringBad&);
        StringBad& operator=(StringBad&&);
        StringBad& operator=(const char* s);
        ~StringBad();
        friend std::ostream& operator<<(std::ostream& out, const StringBad& src);
        friend std::istream& operator>>(std::istream& in, StringBad& src);
        bool operator<(const StringBad& src);
        bool operator>(const StringBad& src);
        bool operator==(const StringBad& src);
        char& operator[](int index);
        const char& operator[](int index) const;
        static int HowMany();
};
