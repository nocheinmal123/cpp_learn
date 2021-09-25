#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>

int calc(const std::string& strsource, char ch){
    std::cout<<"calc 1"<<std::endl;
    const char* p = strsource.c_str();
    int cnt = 0;
    // do some work
    return cnt;
}

int calc(std::string& strsource, char ch){
    std::cout<<"calc 2"<<std::endl;
    const char* p = strsource.c_str();
    int cnt = 0;
    // do some work
    return cnt;
}

int main(){
    char str1[100] = "this a test.";
    int res1 = calc(str1,'i');

    std::string str2 = "this is a test";
    int res2 = calc(str2,'i');

    const std::string str3 = "this is a test";
    int res3 = calc(str3,'i');    
    return 0;
}
/*
Output:
calc 1
calc 2
calc 1
*/