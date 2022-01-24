#include "13_dma.h"

int main(){
    using std::cin;
    using std::cout;
    using std::endl;
    baseDMA shirt("Portabelly",8);
    lacksDMA ballon("red", "Blimpo", 5);
    hasDMA map("Mercator", "Buffalo Keys", 5);
    cout << shirt << endl;
    cout << ballon << endl;
    cout << map << endl;
    lacksDMA ballon2(ballon);
    lacksDMA ballon3("yellow", shirt);
    cout << ballon2 << endl;
    cout << ballon3 << endl;
    hasDMA map2;
    map2 = map;
    cout << map2 << endl;
    return 0;
}