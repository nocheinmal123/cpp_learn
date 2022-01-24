#include <iostream>
#include <string.h>
#include <string>
namespace SALES{
    class Sales{
        private:
            double* sales;
            double average;
            double max_val;
            double min_val;
            void cal(const int n);
        public:
            Sales(const double* arr, int n){
                std::cout << "con called" << std::endl;
                sales = NULL;
                sales = new double[n];
                memcpy(sales, arr, n*sizeof(double));                
                cal(n);
            }
            Sales(const Sales& sale){
                std::cout << "Copy con called" << std::endl;
                int n = sizeof(sale.sales)/sizeof(double);
                std::cout << "in copy con, n = " << n << std::endl;
                sales = new double[n];
                memcpy(sales, sale.sales, n*sizeof(double));
                average = sale.average;
                max_val = sale.max_val;
                min_val = sale.min_val;
            }
            ~Sales(){
                delete[] sales;
                sales = NULL;
            }
            void setSales(const double* arr, int n);
            void setSales();
            void showSales() const;
    };
}