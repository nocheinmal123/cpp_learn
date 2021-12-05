#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

struct CandyBar{
    char *name;
    double weight;
    int calorie;
    ~CandyBar(){
        delete[] name;
        name = NULL;
    }
};

void set_candybar(CandyBar& candy, char* s = "Millenium Munch", double weight = 2.85, int calorie = 350){
    int n = strlen(s);
    candy.name = new char[n + 1];
    memcpy(candy.name, s, n*sizeof(char));
    candy.weight = weight;
    candy.calorie = calorie;
}

void show_candybar(const CandyBar& candy){
    std::cout << "name = " << candy.name << std::endl;
    std::cout << "weight = " << candy.weight <<  std::endl;
    std::cout << "calorie = " << candy.calorie << std::endl;
}

int main(){
    CandyBar candy;
    set_candybar(candy);
    show_candybar(candy);
    return 0;
}