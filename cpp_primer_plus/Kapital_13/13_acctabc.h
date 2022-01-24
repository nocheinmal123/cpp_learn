#include <iostream>
#include <string>

// Abstract Base Class
class AcctABC{
    private:
        std::string _fullname;
        int _acctNum;
        double _balance;
    protected:
        const std::string& FullName() const{ return _fullname;}
        int AcctNum() const{ return _acctNum;}
    public:
        AcctABC(const std::string& s = "Nullbody", int an = -1,
                double bal = 0);
        AcctABC(const AcctABC&);
        void Deposit(double amt);
        virtual void Withdraw(double amt) = 0;
        double Balance() const { return _balance;}
        virtual void ViewAcct() const = 0;
        virtual ~AcctABC(){}
};

class Brass: public AcctABC{
    public:
        Brass(const std::string&s = "Nullbody", int an = -1,
            double bal = 0):AcctABC(s, an, bal){}
        virtual void Withdraw(double amt);
        virtual void ViewAcct() const;
        virtual ~Brass() {}
};

class BrassPlus: public AcctABC{
    private:
        double _maxLoan;
        double _rate;
        double _owesbank;
    public:
        BrassPlus(const std::string& s = "Nullbody", int an = -1,
                double bal = 0, double ml = 500,
                double r = 0.1);
        BrassPlus(const Brass& ba, double ml = 500, double  = 0);
        virtual void Withdraw(double amt);
        virtual void ViewAcct() const;
        void ResetMax(double m) { _maxLoan = m;}
        void ResetRate(double r) { _rate = r;}
        void ResetOwes() { _owesbank = 0;}
};