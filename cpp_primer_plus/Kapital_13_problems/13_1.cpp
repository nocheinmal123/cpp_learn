#include "13_1.h"

void Bravo(const Cd& disk){
    disk.Report();
}

int main(){
    Cd c1("Beatles", "Capitol", 14, 35.5);
    Classic c2 = Classic("Piano Sonata in B flat, Fantasia in C", "Alfred Brendel", "Philips", 2, 57.17);
    Cd* pcd = &c1;
    std::cout << "Using object directly:\n";
    c1.Report();
    c2.Report();
    std::cout << std::endl;

    pcd->Report();
    pcd = &c2;
    pcd->Report();
    std::cout << std::endl;

    std::cout << "In function bravo:" << std::endl;
    Bravo(c1);
    Bravo(c2);
    std::cout << std::endl;

    Classic copy;
    copy = c2;
    copy.Report();
    return 0;
}