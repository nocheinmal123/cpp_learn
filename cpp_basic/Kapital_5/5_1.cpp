#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Student{
    private:
        std::string name;
        int age;
    public:
        bool IsThreeGood();
        void Setname(const std::string &name);
};

class UndergraduateStudent: public Student{
    private:
        int nDepartment;
    public:
        bool IsThreeGood();
        bool CanBaoYan();
};

class GraduateStudent: public Student{
    private:
        int nDepartment;
        char szMentorName[20];
    public:
        int CountSalary();
};

class CBase{
    int v1,v2;
};

class CDerived: public CBase{
    int v3;
};

/*
                <---  v1  ---> CBase
    CDerived    <---  v2  ---> 
                <---  v3

sizeof(CDerived) = sizeof(CBase) + sizeof(element,which only belong to CDerived)
*/


int main(){
    return 0;
}