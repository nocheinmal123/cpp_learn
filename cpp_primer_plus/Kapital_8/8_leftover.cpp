#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

int left(int num, int n){
    if(n < 0) n = 0;
    int cnt = 0;
    int temp_num = num;
    while(temp_num){
        cnt ++;
        temp_num /= 10;
    }
    if(cnt <= n) return num;
    else{
        temp_num = num;
        int counter = cnt - n;
        while(counter --){
            temp_num /= 10;
        }
        return temp_num;
    }
}

std::shared_ptr<std::string> left(std::shared_ptr<std::string> s, int n){
    if(n < 0) n = 0;
    int len = (s.get())->length();
    n = std::min(n, len);
    std::shared_ptr<std::string> ptr = std::make_shared<std::string>(*(s.get()), 0, n);
    return ptr; 
 }

int main(){
    int num = 134256;
    for(int i=1;i<=20;i++){
        std::cout << left(num, i) << std::endl;
    }
    std::shared_ptr<std::string> s = std::make_shared<std::string>("hawai !!!!!!!!!!!");
    // shared_ptr can also be initalized like below
    // std::shared_ptr<std::string> s(new std::string("fasdfasdf")); 
    for(int i=1;i<=20;i++){
        std::shared_ptr<std::string> temp_s = left(s, i);
        std::cout << *temp_s << std::endl;
    }
    return 0;
}