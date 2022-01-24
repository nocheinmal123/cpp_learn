#include "12_strngbad.h"
#include <iostream>
const int ArSize = 10;
const int MaxLen = 81;

int main(){
    using std::cout;
    using std::cin;
    using std::endl;

    StringBad name;
    cout << "What's your name?\n";
    cin >> name;
    cout << name << endl;
    name[0] = 'p';
    cout << name << endl;
    StringBad name2 = name;
    StringBad name3 = std::move(name2);
    name3 = "lvyilin";
    cout << name3 << endl;
    StringBad name4("dfsadf");
    cout << (name3 < name4) << endl;
    cout << (name3 == name4) << endl;
    cout << (name3 > name4) << endl;

    const StringBad name6("hhhhh");  //const overload [] will be called
    cout << name6[0] << endl;
    return 0;
}