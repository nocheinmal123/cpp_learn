#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// reload of  assignment operation "=" the reload _operation_4_2
// just finish the job, which can obj = "hello"
// but it still has problem, when we wanna do like obj1 = obj2

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
        String(const String &s){ //self-defined copy con, to avoid 
        // similar problem, just like when using "obj1 = obj2"
            std::cout<<"copy con"<<std::endl;
            str = new char[strlen(s.str)+1];
            strcpy(str,s.str);
        }
};

String & String::operator=(const String &s){ 
    if(this == &s){
        return *this;
        /*
        String s = "hello";
        s = s
        */
    }
    delete []str;
    str = new char[strlen(s.str)+1];
    strcpy(str,s.str);
    return *this;
}

int main(){

    char x1[]="this", x2[]="that";
    String s1(x1),s2(x2);
    s1 = s2;
    char now[] = "other";
    s2 = now; // s1 will not be changed, deep copy
    // plus, here a temp-value will be generated, cauz "now" will call the construtor function
    printf("s1 = %s\n",s1.getValue());
    printf("s2 = %s\n",s2.getValue());

    String s3(s2);
    return 0;
}

/*
Why should we use a ref as the return value of reload operation ?
1.We can use "void" as the return value, but it will have a problem,such as follow:
a = b = c;
firstly, "b = c" will be excuted, the return value of this assignment is "void",
so in the next step, we let "a = (void)", it is apparently wrong.

2. We wanna to keep a character of "=", such as follow:
(a = b) = c;
Firstly, (a = b) will be excuted, and the return value is a ref of a, 
so in the next step, a will be changed from b to c. That is what we want.

So, we use a ref as the return value for the reload operation
*/