#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <future>

int main() {
    std::string s = "Hi.";
    std::cout << s.size() << std::endl;
    const char* str = s.c_str();
    std::cout << sizeof(str) << std::endl;
    return 0;
}