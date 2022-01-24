#include "11_4_time.h"
#include "11_7_complex.h"

int main(){
    using namespace TIME;
    Time t1(5,34);
    std::cout << t1 << std::endl;
    Time t2 = t1++;
    std::cout << t2 << ",  " << t1 << std::endl;
    ++t1;
    std::cout << t1 << std::endl;
    Time t3(1,45);
    std::cout << t1 + t3 << std::endl;
    t3 = 2 * t3;
    std::cout << t3 << std::endl;
    t3--;
    std::cout << t3 << std::endl;
    t3[2] = 'i';
    std::cout << t3 << std::endl;

    using namespace COMPLEX;
    
    return 0;
}