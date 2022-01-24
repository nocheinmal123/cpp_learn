#include "12_1.h"

Cow::Cow(){
    strcpy(_name, "");
    _hobby = nullptr;
    _weight = 0;
}

Cow::Cow(const char* nm, const char* ho, double wt){
    strcpy(_name, nm);
    int len = strlen(ho);
    _hobby = new char[len + 1];
    strcpy(_hobby, ho);
    _weight = wt;
}

Cow::Cow(const Cow& c){
    strcpy(_name, c._name);
    int len = strlen(c._hobby);
    _hobby = new char[len + 1];
    strcpy(_hobby, c._hobby);
    _weight = c._weight;
}

Cow& Cow::operator=(const Cow& c){
    if(this == &c) return *this;
    stpcpy(_name, c._name);
    int len = strlen(c._hobby);
    _hobby = new char[len + 1];
    _weight = c._weight;
}

void Cow::ShowCow() const{
    std::cout << "name: " << _name << std::endl;
    std::cout << "hobby: " << _hobby << std::endl;
    std::cout << "weight: " << _weight << std::endl;
}

Cow::~Cow(){
    delete[] _hobby;
}