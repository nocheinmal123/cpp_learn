#include <string>
#include <iostream>
#include <string.h>

// Brass Account Class
class Brass{
    private:
        std::string _fullName;
        int _acctNum;
        double _balance;
    public:
        Brass(const std::string& s = "NULLbody", int acctNum = -1, double balance = 0);
        Brass(const Brass&);
        Brass& operator=(const Brass&);
        Brass& operator=(Brass&&);
        void Deposit(double amt);
        virtual void Withdraw(double amt) ;
        double Balance() const;
        virtual void ViewAcct() const ;
        virtual ~Brass(); //基类使用虚析构函数是为了保证，释放派生类对象的时候，能够按正确的顺序调用析构函数
        // 如果不使用虚析构函数，那么Brass* p = new BrassPlus(),及时p指向了派生类，
        // 也只有基类被释放，派生类不会被释放
};

class BrassPlus: public Brass{
    private:
        double _maxLoan;
        double _rate;
        double _owesBank;
    public:
        BrassPlus(const std::string& s = "NULLbody", int acctNum = -1, 
                double balance = 0, double maxLoan = 500, 
                double rate = 0.11125);
        BrassPlus(const Brass& ba, double maxLoan = 500,
                double rate = 0.11125);
        BrassPlus& operator=(const BrassPlus&);
        BrassPlus& operator=(BrassPlus&&);
        virtual void ViewAcct() const override;
        virtual void Withdraw(double amt) override;
        void ResetMax(double m) { _maxLoan = m; }
        void ResetRate(double r) { _rate = r; }
        void ResetOwes(){ _owesBank = 0; }
};