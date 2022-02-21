#include <string>
#include <string.h>
#include <iostream>

class Worker{
    private:
        char* _fullname;
        int _id;
    public:
        explicit Worker(const char* fullname = "non one", int id = 0);
        Worker(const Worker& wk);
        virtual ~Worker();
        virtual void Set();
        virtual void Show() const;
};

class Waiter: public Worker{
    private:
        int _panache;
    public:
        Waiter(const char* fullname, int id, int panache = 0);
        Waiter(const Worker& wk,int panache = 0);
        ~Waiter(){}
        virtual void Set() override;
        virtual void Show() const override;
};

class Singer: public Worker{
    private:
        char* pv;
        int voice;
    public:
        Singer():Worker(), voice(0){}
        Singer(const char* fullname, int id, int v = 0);
        Singer(const Worker& wk, int v = 0);
        ~Singer(){}
        virtual void Set() override;
        virtual void Show() const override;
};