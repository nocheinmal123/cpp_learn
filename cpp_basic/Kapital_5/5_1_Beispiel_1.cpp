#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class CUndergraduateStudent;
class CStudent{
    private:
        std::string name;
        std::string id;
        char gender;
        int age;
    public:
        void PrintInfo() const;
        void SetInfo(const std::string &name_,const std::string &id_,const int age_,const char gender_);
        std::string Getname() const;
    friend std::ostream& operator<<(std::ostream& out,const CStudent& c);
};

std::ostream& operator<<(std::ostream& out,const CStudent& c){
    out<<c.name<<" "<<c.id<<" "<<c.gender<<" "<<c.age;
    return out;
}

void CStudent::PrintInfo() const{
    std::cout<<"CStudent PrintInfo called"<<std::endl;
    std::cout<<name<<" "<<id<<" "<<gender<<" "<<age<<std::endl;
}

void CStudent::SetInfo(const std::string &name_,const std::string &id_,const int age_,const char gender_){
    std::cout<<"CStudent SetInfo called"<<std::endl;
    name = name_; id = id_; age = age_; gender = gender_;
}

std::string CStudent::Getname() const{
    return name;
}

class CUndergraduateStudent: public CStudent{
    private:
        std::string department;
    public:
        void Qualified();
        void PrintInfo() const; //override of the same func of base class
        // SetInfo is not override, cauz the parameter are not same, it is just a new method
        void SetInfo(const std::string &name_,const std::string &id_,const int age_,const char gender_,const std::string department_); 

};

void CUndergraduateStudent::Qualified(){
    std::cout<<"Qualified for Graduate"<<std::endl;
}

void CUndergraduateStudent::PrintInfo() const{
    CStudent::PrintInfo(); //call of function of father class
    std::cout<<department<<std::endl;
}

void CUndergraduateStudent::SetInfo(const std::string &name_,const std::string &id_,const int age_,const char gender_,const std::string department_){
    CStudent::SetInfo(name_,id_,age_,gender_); //call of function of class
    department = department_;
}

int main(){
    CUndergraduateStudent s2;
    s2.SetInfo("FangSen","201142049",19,'M',"CS");
    std::cout<<s2.Getname()<<std::endl;
    s2.Qualified();
    s2.PrintInfo();
    s2.CStudent::PrintInfo();
    return 0;
}