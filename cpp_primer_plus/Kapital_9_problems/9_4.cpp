#include "9_4.h"
#include "algorithm"
namespace SALES{
    void Sales::cal(const int n){
        max_val = -1;
        min_val = 100000000;
        double sum = 0;
        for(int i=0;i<n;i++){
            max_val = std::max(max_val, sales[i]);
            min_val = std::min(min_val, sales[i]);
            sum += sales[i];
        }
        average = sum/n;
    }
    void Sales::setSales(const double* arr, int n){
        sales = new double[n];
        memcpy(sales, arr, n*sizeof(double));
        cal(n);
    }
    void Sales::setSales(){
        int n;
        std::cout << "Enter the num of sales:  ";
        std::cin >> n;
        sales = new double[n];
        for(int i=0;i<n;i++){
            std::cout << "Enter val of sales:   ";
            std::cin >> sales[i];
        }
        cal(n);
    }
    void Sales::showSales() const{
        std::cout << "Max = " << max_val << std::endl;
        std::cout << "Min = " << min_val << std::endl;
        std::cout << "average = " << average <<  std::endl;
    }
}