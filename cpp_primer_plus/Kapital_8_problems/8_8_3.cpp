#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

std::shared_ptr<std::string> Upper(std::shared_ptr<std::string> s){
    int len = s.get()->length();
    for(int i=0;i<len;i++){
        (*s)[i] = std::toupper((*s)[i]);
    } 
    return s;
}

void Show(){
    std::string s;
    int cnt = 0;
    while(1){
        if(!cnt) std::cout << "Enter a string (q to quit): ";
        else std::cout << "Next string (q to quit): ";
        std::cin >> s;
        if(s == "q"){
            std::cout << "Bye." << std::endl;
        }
        std::shared_ptr<std::string> s_ptr = std::make_shared<std::string>(s);
        std::cout << *Upper(s_ptr) <<  std::endl;
        cnt ++;
    }
}

int main(){
    Show();
    return 0;
}