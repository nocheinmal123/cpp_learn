#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Let's compare the difference between
1. String & String::operator=(const String &s)
and
2. String & String::operator=(const char *s)

Differences:
1. Different uses, to fullfill obj1 = obj2, we have to use 1
2. The num of calling of constructor
*/

class String{
    private:
        char *str;
    public:
        String(char *x){
            str = new char[strlen(x)+1];
            strcpy(str,x);
            printf("con called!\n");
        }
        const char *getValue(){
            return str;
        }
        String & operator=(const String &s);
        ~String(){
            delete []str;
        }
        // String & operator=(const char *s);
};

String & String::operator=(const String &s){
    delete []str;
    str = new char[strlen(s.str)+1];
    strcpy(str,s.str);
    return *this;
}

// String & String::operator=(const char *s){
//     delete []str;
//     str = new char[strlen(s)+1];
//     strcpy(str,s);
//     return *this;
// }

int main(){
    char x[] = "lalalal";
    String s(x);
    char now[] = "nownow";
    s = now;
    // tow times "con called", when "s = now" is being excuted,
    // firstly, a temp-obj will be generated, cauz,the parameter of the
    // reload function if a ref of class, so a temp-obj will be generated.
    return 0;
}

/*
But is we use the commeted statements, only one time "con called"
will be generated.
*/