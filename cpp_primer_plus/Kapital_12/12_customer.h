#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>

class Customer{
    private:
        int _arrivetime; 
        int _processtime;
    public:
        Customer();
        void set(int _when);
        int when() const;
        int ptime() const;
};