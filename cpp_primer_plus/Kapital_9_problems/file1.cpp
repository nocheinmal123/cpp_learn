#include <iostream>
int x = 10;
int y;

void other(){
    int y = 1;
    std::cout <<"Other: " << x << ", " << y <<std::endl;
}

void another();

int main(){
    std::cout << x <<std::endl;
    {
        int x = 4,y = 17;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
    }
    other();
    another();
    return 0;
}