#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
// locator value: the vars, which have definate adress in the ROM
// read value: the vars, which cannot be "get adressed"
// && ref of the rvalue
class A{};

class String{
    public:
        char *str;
        String():str(new char[1]){
            str[0] = 0;
        }
        String(const char* s){
            str = new char[strlen(s) + 1];
            strcpy(str,s);
        }
        String(const String& s){
            std::cout<<"copy con called"<<std::endl;
            str = new char[strlen(s.str) + 1];
            strcpy(str,s.str);
        }
        String& operator=(const String& s){
            std::cout<<"reload operator ="<<std::endl;
            if(str != s.str){
                delete []str;
                str = new char[strlen(s.str) + 1];
                strcpy(str,s.str);
            }
            return *this;
        }
        // move constructor, no deep copy
        String(String&& s):str(s.str){
            std::cout<<"move con called"<<std::endl;
            s.str = new char[1];
            s.str[0] = 0;
        }
        // move assignment
        String& operator=(String&& s){
            std::cout<<"reload operator move"<<std::endl;
            if(str != s.str){                          
                delete []str;
                str = s.str;                                 
                s.str = new char[1];                        
                s.str[0] = 0;                                  
            }
            return *this;
        }
        ~String(){
            delete []str;
        }
};

template <class T>
void MoveSwap(T& a,T& b){
    T temp(std::move(a)); // std::move(a) is the rvalue of a, move con called, a is now an empty string
    a = std::move(b); // move(b) is the rvalue, move assignment called, b is now an empty string
    b = std::move(temp); // move(temp) is the rvalue,move assignment called, temp is now an empty string
}

int main(){
    // A& r = A(); error, A() is a var without name, it is a rvalue
    A&& r = A(); // && is the ref of rvalue
    int&& t = 100;

    String s;
    return 0;
}