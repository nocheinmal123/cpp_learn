#include <string>
#include <string.h>
#include <iostream>

class Cow{
    private:
        char _name[20];
        char *_hobby;
        double _weight;
    public:
        Cow();
        Cow(const char* nm, const char* ho, double wt);
        Cow(const Cow& C);
        ~Cow();
        Cow& operator=(const Cow& c);
        void ShowCow() const;
};