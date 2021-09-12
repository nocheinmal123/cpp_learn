#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Time{
    private:
        int Hour;
        int Minute;
    public:
        Time(int h,int m):Hour(h),Minute(m){

        }
        Time& operator=(const Time& t);
};

Time& Time::operator=(const Time& t){
    Hour += t.Hour;
    Minute += t.Minute;
    return *this;
}

class String{
    private:
        char* p;
    public:
        String(char* s);
        ~String();
        String& operator=(const char* s);
        String& operator=(const String& s);
        char* getValue() const;
};

// ************************************************************
// compare the difference of reload operator= when using ref and using pointer
String::String(char* s){
    std::cout<<"con called"<<std::endl;
    // if(p !=NULL) delete []p;
    p = new char[strlen(s) + 1];
    strcpy(p,s);
}

String::~String(){
    std::cout<<"decon called"<<std::endl;
    delete []p;
}

String& String::operator=(const char* s){
    std::cout<<"reload through pointer"<<std::endl;
    if(p != NULL) delete []p;
    p = new char[strlen(s) + 1];
    stpcpy(p,s);
    return *this;
}

String& String::operator=(const String& s){
    std::cout<<"reload through ref"<<std::endl;
    if(p != NULL) delete []p;
    p = new char[strlen(s.p) + 1];
    strcpy(p,s.p);
    return *this;
}

char* String::getValue() const{
    return p;
}

int main(){
    char x1[] = "x1";
    char x2[] = "x2";
    char x3[] = "x3";
    String s1(x1);
    String s2(x2);
    String s3(x3);

    char x4[] = "x4";
    s1 = x4;
    s2 = s3;
    std::cout<<*(s2.getValue())<<std::endl;
    return 0;
}

/*
con called
con called
con called
reload through pointer
reload through ref
x
decon called
decon called
decon called
*/