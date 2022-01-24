#include "10_10_2.h"

Person::Person(){
    lname = "";
    fname = NULL;
}

Person::Person(const std::string& _lname, const char* _fname){
    lname = _lname;
    int len = strlen(_fname);
    fname = new char[len];
    memcpy(fname, _fname, len*sizeof(char));
}

Person::~Person(){
    delete[] fname;
}

void Person::show() const{
    if(fname) std::cout << fname << " " << lname << std::endl;
}

void Person::FormalShow() const{
    if(fname) std::cout << lname << ", " << fname << std::endl;
}