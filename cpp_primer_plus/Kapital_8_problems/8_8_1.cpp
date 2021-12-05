#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template<typename T>
void show(std::shared_ptr<T> s, int k){
    if(k == 0) return;
    else{
        std::cout << *s << std::endl;
        show(s, k - 1);
    }
}

int main(){
    std::shared_ptr<std::string> s = std::make_shared<std::string>("fangsen1234");
    show(s, 4);
    return 0;
}