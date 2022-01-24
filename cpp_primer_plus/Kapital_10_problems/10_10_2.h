#include <iostream>
#include <string>
#include <string.h>

class Person{
    private:
        std::string lname;
        char* fname;
    public:
        Person();
        Person(const std::string& _lname, const char* _fname = "Heyyou");
        ~Person();
        void show() const;          // firstname lastname format
        void FormalShow() const;    // lastname, firstname format
};
