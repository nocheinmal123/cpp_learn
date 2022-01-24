#include "13_brass.h"

Brass::Brass(const std::string& s, int acctNum, double balance){
    _fullName = s;
    _acctNum = acctNum;
    _balance = balance;
}

Brass::Brass(const Brass& ba){
    _fullName = ba._fullName;
    _acctNum = ba._acctNum;
    _balance = ba._balance;
}

Brass& Brass::operator=(const Brass& ba){
    if(this == &ba) return *this;
    _fullName = ba._fullName;
    _acctNum = ba._acctNum;
    _balance = ba._balance;
}

Brass& Brass::operator=(Brass&& ba){
    if(this == &ba) return *this;
    _fullName = ba._fullName;
    _acctNum = ba._acctNum;
    _balance = ba._balance;
}

Brass::~Brass(){}

void Brass::Deposit(double amt){
    if(amt < 0){
        std::cout << "Negative deposit not allowed, deposit is cacalled.\n";
    }
    else _balance += amt;
}

void Brass::Withdraw(double amt){
    if(amt < 0){
        std::cout << "Withdraw amount must be positive, withdraw is cancelled.\n";
    }
    else if(amt <= _balance){
        _balance -= amt;
    }
    else{
        std::cout << "Withdraw amount exceeds your balance. Withdraw cancalled.\n";
    }
}

double Brass::Balance() const{
    return _balance;
}

void Brass::ViewAcct() const{
    std::cout << "Client: " << _fullName << std::endl;
    std::cout << "Account Nr.: " << _acctNum << std::endl;
    std::cout << "Balance: " << _balance << std::endl;
}

BrassPlus::BrassPlus(const std::string& s, int acctNum, double balance,
                    double maxLoan, double rate):Brass(s, acctNum, balance){
   _maxLoan = maxLoan;
   _rate = rate; 
   _owesBank = 0;
}

BrassPlus::BrassPlus(const Brass& ba, double maxLoan, double rate):Brass(ba){
    _maxLoan = maxLoan;
    _rate = rate;
    _owesBank = 0;
}

BrassPlus& BrassPlus::operator=(const BrassPlus& bap){
    if(this == &bap) return *this;
    Brass::operator=(bap);
    _maxLoan = bap._maxLoan;
    _rate = bap._rate;
    _owesBank = bap._owesBank; 
}

BrassPlus& BrassPlus::operator=(BrassPlus&& bap){
    if(this == &bap) return *this;
    Brass:operator=(bap); //不能使用，因为这个重载运算符是利用右值，吊用完了之后bap就无法在使用了
    _maxLoan = bap._maxLoan;
    _rate = bap._rate;
    _owesBank = bap._owesBank;
}

void BrassPlus::ViewAcct() const{
    Brass::ViewAcct();
    std::cout << "Maximum loan: " << _maxLoan << std::endl;
    std::cout << "Owed to bank: " << _owesBank << std::endl;
    std::cout << "Loan rate: " << _rate << std::endl;
}

void BrassPlus::Withdraw(double amt){
    double bal = Balance();
    if(amt <= bal){
        Brass::Withdraw(amt);
    }
    else if(amt <= bal + _maxLoan - _owesBank){
        double advance = amt - bal;
        _owesBank = advance * (1 + _rate);
        std::cout << "Bank advance: " << advance << std::endl;
        std::cout << "Finance charge: " << advance * _rate << std::endl;
        Deposit(advance);
        Brass::Withdraw(amt);
    }
    else std::cout << "Credits limit exceeded. Transition cancalled.\n";
}