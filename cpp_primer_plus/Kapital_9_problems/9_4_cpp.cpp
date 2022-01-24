#include "9_4.h"
#include <memory>

void func(){
    using namespace SALES;
    double arr[] = {10.1,100, 14.64, 7.8};
    std::shared_ptr<Sales> pr = std::make_shared<Sales>(arr, 4);
    pr->showSales();
    double arr2[] = {1.1, 1.4, 0, 89, 56.33};
    pr->setSales(arr2, 5);
    pr->showSales();
    pr->setSales();
    pr->showSales();
    // printf("%lf\n",arr[0]);
    double arr3[] = {12.3, 15.9};
    Sales sa(arr3, 2);
    Sales sb(sa);
    // sa.showSales();
    // Sales sb(sa);
    // sb.showSales();
}

int main(){
    func();
    return 0;
}