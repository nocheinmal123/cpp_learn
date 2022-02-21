#include <iostream>
#include <string.h>
#include <string>

class Worker{
    private:
        std::string fullname_;
        int id_;
    protected:
        virtual void Data() const;
        virtual void Get();
    public:
        Worker();
        Worker(const std::string&, int);
        Worker(const Worker&);
        virtual ~Worker() = 0;
        virtual void Set() = 0;
        virtual void Show() const = 0;
};

class Waiter: virtual public Worker{
    private:
        int panache_;
    protected:
        virtual void Data() const;
        virtual void Get();
    public:
        Waiter();
        Waiter(const std::string&, int , int);
        Waiter(const Worker&, int);
        ~Waiter() {}
        virtual void Set();
        virtual void Show() const;
};

class Singer: virtual public Worker{
    private:
        int voice_;
    protected:
        virtual void Data() const;
        virtual void Get();
    public:
        Singer();
        Singer(const std::string&, int, int );
        Singer(const Worker&, int);
        ~Singer() {}
        virtual void Set();
        virtual void Show() const;
};

class Singingwaiter: public Singer, public Waiter{
    protected:
        void Data() const;
        void Get();
    public:
        Singingwaiter();
        Singingwaiter(const std::string&, int, int, int);
        Singingwaiter(const Worker&, int , int);
        Singingwaiter(const Waiter&, int);
        Singingwaiter(const Singer&, int);
        ~Singingwaiter() {}
        virtual void Set();
        virtual void Show() const;
};