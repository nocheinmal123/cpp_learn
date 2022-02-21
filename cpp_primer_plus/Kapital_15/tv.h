#include <iostream>
#include <string>
#include <string.h>
/*
什么时候使用有元类呢？
比如通过类A来改变类B内部的状态时候，则可以在类B中申明class A
是他的有元
*/

class Tv{
    private:
        int state;      // on or off
        int volume;
        int maxchannel; // max number of channels
        int channel;    // current channel settting
        int mode;       // broadcast or cable
        int input;      // TV or DVD
    public:
        friend class Remote;
        enum {OFF, ON};
        enum {MINVAL, MAXVAL = 20};
        enum {ANTENNA, CABLE};
        enum {TV, DVD};
        Tv(int s = OFF, int mc = 125): state(s), volume(5), maxchannel(mc), channel(2), mode(CABLE), input(TV){

        }
        void onoff() {state = (state == ON)? OFF : ON;}
        bool ison() const { return state == ON;}
        bool volup();
        bool voldown();
        void chanup();
        void chandown();
        void set_mode() {mode = (mode == ANTENNA)? CABLE : ANTENNA;}
        void set_input() {input = (input == TV)? TV : DVD;}
        void settings() const;  //display all settings
};

class Remote{
    private:
        int mode; // controls TV of DVD
    public:
        Remote(int m = Tv::TV): mode(m) {}
        bool volup(Tv& t) { return t.volup(); }
        bool voldown(Tv& t) { return t.voldown();}
        void onoff(Tv& t) { t.onoff();}
        void chanup(Tv& t) { t.chanup();}
        void chandown(Tv &t) { t.chandown();}
        void set_chan(Tv &t, int c) { t.channel = c;}
        void set_mode(Tv &t) { t.set_mode();}
        void set_input(Tv &t) { t.set_input();}
};