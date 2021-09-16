#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
// const_cast, used to delete the "const" character,
// const ref -> normal ref
// const pointer -> normal pointer


int main(){
    const std::string s = "Inception";
    std::string& p = const_cast<std::string&>(s);
    std::string* ps = const_cast<std::string*>(&s); // the type of &s is const string*
    return 0;
}