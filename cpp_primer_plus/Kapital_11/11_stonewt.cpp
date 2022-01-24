#include "11_stonewt.h"

namespace STONE{
    Stonewt::Stonewt(double lbs){
        std::cout << "con 1 called.\n";
        stone = int (lbs) / (int)Weight::Lbs_per_stn;
        pds_left = lbs - stone * (int)Weight::Lbs_per_stn;
        pounds = lbs;
    }

    Stonewt::Stonewt(int stn, double lbs){
        stone = stn;
        pds_left = lbs;
        pounds = stn * (int)Weight::Lbs_per_stn + lbs;
    }

    Stonewt::Stonewt(){
        stone = pounds = pds_left = 0;
    }

    Stonewt::~Stonewt(){

    }

    void Stonewt::show_stn() const{
        std::cout << stone << " stone, " << pds_left << " pounds.\n";
    }

    void Stonewt::show_lbs() const{
        std::cout << pounds << " pounds.\n";
    }

    Stonewt::operator double() const{
        return pounds;
    }

    Stonewt::operator int() const{
        return int(pounds + 0.5);
    }
}