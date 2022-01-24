#include "12_customer.h"

Customer::Customer(){
    _arrivetime = _processtime = 0;
}

void Customer::set(int _when){
    _processtime = std::rand()%3 + 1;
    _arrivetime = _when;
}

int Customer::when() const{
    return _arrivetime;
}

int Customer::ptime() const{
    return _processtime;
}