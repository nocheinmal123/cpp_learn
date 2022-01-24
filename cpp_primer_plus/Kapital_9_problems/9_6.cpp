#include "9_6.h"
#include <iostream>
namespace Golf{
    void golf::setgolf(const char* _fullname, const int _hc){
        fullname = NULL;
        fullname = new char[strlen(_fullname) + 1];
        memcpy(fullname, _fullname, (strlen(_fullname) + 1)*sizeof(char));
        handicap = _hc;
    }
    void golf::setgolf(){
        using namespace std;
        cout << "Enter a name: ";
        cin >> fullname;
        cout << "Enter a handicap: ";
        cin >> handicap;
    }
    void golf::sethandicap(const int _hc){
        handicap = _hc;
    }
    void golf::showgolf() const{
        std::cout << "name: " << fullname << std::endl;
        std::cout << "handicap: " << handicap << std::endl;
    }
}
