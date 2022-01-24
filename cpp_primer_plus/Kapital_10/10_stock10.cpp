#include "10_stock10.h"
#include <iostream>

Stock::Stock(){
    std::cout << "Default constructor called\n";
    company = "no name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}

Stock::Stock(const std::string& co, long n, double pr){
    using std::cout;
    cout << "con called" << std::endl;
    company = co;
    if(n < 0){
        std::cout << "Number of shares can't be negative; " << company << " shares set to 0.\n";
        shares = 0;
    }
    else shares = n;
    share_val = pr;
    set_tot();
}

Stock::Stock(const Stock& _stock){
    using std::cout;
    cout << "copy con called" << std::endl;
    company = _stock.company;
    shares = _stock.shares;
    share_val = _stock.share_val;
    total_val = _stock.total_val;
}

Stock::~Stock(){
    using std::cout;
    cout << "Bye, " << company << "!\n";
}

void Stock::buy(long num, double price){
    if(num < 0){
        std::cout << "Number of shares purchase can't be negative. " << "Transition is aborted.\n";
    }
    else{
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price){
    using std::cout;
    if(num < 0){
        cout << "Number of shares sold can't be nagative. " << "Transition is aborted.\n";
    }
    else if(num > shares){
        cout << "You can't sell more than you have! " << "Transition is aborted.\n";
    }
    else{
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price){
    share_val = price;
    set_tot();
}

const Stock& Stock::topval(const Stock& s) const{
    if(this->total_val > s.total_val) return *this;
    else return s;
}

void Stock::show() const{
    using std::cout;
    cout << "Comapny: " << company << std::endl;
    cout << "Shares: " << shares << std::endl;
    cout << "Share_val: " <<  share_val << std::endl;
    cout << "Total: " << total_val << std::endl;
}

