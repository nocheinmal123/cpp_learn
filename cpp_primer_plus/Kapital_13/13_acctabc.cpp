#include "13_acctabc.h"
using std::cin;
using std::cout;
using std::endl;

AcctABC::AcctABC(const std::string &s, int an, double bal)
{
    _fullname = s;
    _acctNum = an;
    _balance = bal;
}

AcctABC::AcctABC(const AcctABC& src){
    _fullname = src._fullname;
    _acctNum = src._acctNum;
    _balance = src._balance;
}

void AcctABC::Deposit(double amt)
{
    if (amt < 0)
    {
        cout << "Nagative deposit not allowed; "
             << "deposit is cancelled.\n";
    }
    else
    {
        _balance += amt;
    }
}

void AcctABC::Withdraw(double amt)
{
    _balance -= amt;
}


// Brass methods
void Brass::Withdraw(double amt)
{
    if (amt < 0)
    {
        cout << "Withdraw amount must be positve; "
             << "withdraw canceled.\n";
    }
    else if (amt <= Balance())
    {
        AcctABC::Withdraw(amt);
    }
    else
    {
        cout << "Withdraw amount exceeds your balance.\n"
             << "Withdraw canceled.\n";
    }
}

void Brass::ViewAcct() const
{
    cout << "Brass Client: " << FullName() << endl;
    cout << "Account Number: " << AcctNum() << endl;
    cout << "Balance: " << Balance() << endl;
}

// BrassPlus Methods
BrassPlus::BrassPlus(const std::string& s, int an, double bal,
                double ml, double r):AcctABC(s, an, bal){
    _maxLoan = ml;
    _owesbank = 0;
    _rate = r;
}

BrassPlus::BrassPlus(const Brass& ba, double ml, double r): AcctABC(ba){
    _maxLoan = ml;
    _owesbank = 0;
    _rate = r;
}

void BrassPlus::ViewAcct() const{
    cout << "BrassPlus Client: " << FullName() << endl;
    cout << "Account Number: " << AcctNum() << endl;
    cout << "Balance: " << Balance() << endl;
    cout << "Maximum Loan: " << _maxLoan << endl;
    cout << "Owed to back: " << _owesbank << endl;
    cout << "Loan Rate: " << 100 * _rate << endl;
}

void BrassPlus::Withdraw(double amt){
    double bal = Balance();
    if(amt <= bal) AcctABC::Withdraw(amt);
    else if(amt <= bal + _maxLoan - _owesbank){
        double advance = amt - bal;
        _owesbank = advance * (1 + _rate);
        cout << "Bank advance: " << advance << endl;
        cout << "Finance charge: " << advance * _rate << endl;
        Deposit(advance);
        AcctABC::Withdraw(amt);
    }
    else{
        cout << "Credit limit exceed. Transaction cancelled.\n";
    }
}