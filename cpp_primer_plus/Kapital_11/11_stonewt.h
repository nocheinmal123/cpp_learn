#include <string>
#include <string.h>
#include <iostream>

namespace STONE{
    enum class Weight{
        Lbs_per_stn = 14,
    };
    class Stonewt{
        int stone;
        double pds_left;
        double pounds;
    public:
        Stonewt(double lbs);
        // 对于只有一个参数，或者有多个参数，但是除了一个之外的参数，都有default value
        // 那么如果构造函数没有explicit用来修饰，就会发生11_stone.cpp中的情况
        Stonewt(int stn, double lbs);
        Stonewt();
        ~Stonewt();
        Stonewt(Stonewt&& stn){
            std::cout << "move copy con called.\n";
            stone = stn.stone;
            pds_left = stn.pds_left;
            pounds = stn.pounds;
        }
        Stonewt& operator=(Stonewt&& stn){
            std::cout << "moving overload of = called.\n";
            stone = stn.stone;
            pds_left = stn.pds_left;
            pounds = stn.pounds;
            return *this;
        }
        void show_lbs() const;
        void show_stn() const;
// conversion function
       explicit operator double() const;
       explicit operator int() const;
    };
}

