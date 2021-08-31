#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
class CDog; //CDog must be declared firstly
class CMaster{
    CDog *dogs[10]; // cant use CDog dogs[10] !!
};

class CDog{
    CMaster m; //still wrong , many dogs have a same master
    // for example if one dog change the master, so, the dogs, which have
    // the same master must change one by one if using this "obj Method"
    // Instead we should use pointer
};
*/
// Best way is like below
class CMaster;
class CDog{
    CMaster *pm;
};

class CMaster{
    CDog *dogs[10];
};

int main(){
    return 0;
}