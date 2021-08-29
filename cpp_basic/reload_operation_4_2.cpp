#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// reload of  assignment operation "="

class String{
    private:
        char *str;
    public:
        String(char *x){
            str = new char[strlen(x)+1];
            strcpy(str,x);
        }
        const char *getValue(){
            return str;
        }
        String & operator=(const char *s);
        ~String(){
            delete []str;
        }
};

String & String::operator=(const char *s){ //return value is a ref, so
// we can change the obj through this ref
    delete []str;
    str = new char[strlen(s)+1];
    strcpy(str,s);
    return *this; // return a ref, and the ref is *this, so the private
    // var can be changed through reload of "="
}

int main(){
    // reload "=", so we can make obj = "hello"
    char x[]="inital obj";
    String obj(x);
    printf("%s\n",obj.getValue());
    obj = "hello";
    printf("%s\n",obj.getValue());

    // String s = "kkk"; wrong, cauz "=" here means initalization, not 
    // assignment

    char x1[]="s1", x2[]="s2";
    String s1(x1),s2(x2);
    s1 = s2;
    s2 = "now s2"; // s1 will be also changed and it will also cause other problems
    printf("s1 = %s\n",s1.getValue());
    printf("s2 = %s\n",s2.getValue());
    return 0;
}