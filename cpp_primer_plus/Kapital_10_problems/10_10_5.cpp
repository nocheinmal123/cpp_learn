#include "10_10_5.h"

double customer::sum_payment = 0;

customer::customer(const char* _fullname, double _payment){
    int len = strlen(_fullname);
    fullname = new char[len];
    memcpy(fullname, _fullname, len*sizeof(char));
    payment = _payment;
}

customer::customer(const customer& _customer){
    // std::cout << "copy con called" << std::endl;
    int len = strlen(_customer.fullname);
    fullname = new char[len];
    memcpy(fullname, _customer.fullname, len*sizeof(char));
    payment = _customer.payment;
}

customer::customer(){
    fullname = NULL;
    payment = 0;
}

customer& customer::operator=(const customer& _src){
    int len = strlen(_src.fullname);
    this->fullname = new char[len];
    memcpy(this->fullname, _src.fullname, len*sizeof(char));
    this->payment = _src.getPayment();
}

customer::~customer(){
    // std::cout << "customer class decon called.\n" << std::endl;
    delete[] fullname;
}

const char* customer::getFullname() const{
    return fullname;
}

const double customer::getPayment() const{
    return payment;
}