#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

struct stringy{
    std::string name;
    int cnt;
};

template <typename T1, typename T2>
void Set(T1& sample, const T2& name){
    sample = name;
}

template <>
void Set(stringy& sample, const std::string& name){
    sample.name = name;
    sample.cnt = name.length();
}

template <typename T>
void Show(const T& sample,int k = 1){
    while(k--){
        std::cout << sample << std::endl;
    }
}

template <>
void Show(const stringy& sample, int k){
    while(k--){
        std::cout << sample.name << std::endl;
    }
}

int main(){
    char testing[] = "Reality isn't what it used to be.";
    std::string name = "Reality isn't what it used to be.";
    stringy beany;
    std::string s;
    Set(s, name);
    Set(beany, name);
    Show(s);
    Show(s, 2);
    Show(beany);
    Show(beany,4);
    return 0;
}