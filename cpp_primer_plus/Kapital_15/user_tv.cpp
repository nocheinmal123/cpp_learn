#include "tv.h"

int main() {
    Tv s42;
    std::cout << "Initial settings for 42\n";
    s42.settings();
    s42.onoff();
    s42.chanup();
    std::cout << "\nAdjusted settings for 42\n";
    s42.settings();

    Remote grey;
    grey.volup(s42);
    grey.volup(s42);
    std::cout << "settings after using remote:\n";
    s42.settings();
    
    Tv s58(Tv::ON);
    s58.set_mode();
    grey.set_chan(s58, 28);
    std::cout << "s58 settings:\n";
    s58.settings();

    return 0;
}