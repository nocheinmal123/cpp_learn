#include <iostream>
#include <string>
#include <string.h>

class Tv;
class Remote {
    public:
        enum State{OFF, ON};
        enum {MINVAL, MAXVAL = 20};
        enum {ANTENNA, CABLE};
        enum {TV, DVD};
    private:
        int mode;
    public:
        Remote(int m = TV) : mode(m) {} 
        bool volup(Tv& t);
        bool voldown(Tv& t);
        void onoff(Tv& t);
        void chanup(Tv& t);
        void chandown(Tv& t);
        void set_mode(Tv& t);
        void set_input(Tv& t);
        void set_chan(Tv& t, int c);
};

class Tv {
    private:
        int state;
        int volume;
        int maxchannel;
        int channel;
        int mode;
        int input;
    public:
        friend void Remote::set_chan(Tv& t, int c);
        enum State{OFF, ON};
        enum {MINVAL, MAXVAL};
        enum {ANTENNA, CABLE};
        enum {TV, DVD};
        Tv(int s = OFF, int mc = 125):
            state(s), volume(5),
            maxchannel(mc), channel(2),
            mode(CABLE), input(TV) {}
        void onoff() {state = (state == ON)? OFF:ON;}
        bool ison() const {return state == ON;}
        bool volup();
        bool voldown();
        void chanup();
        void chandown();
        void set_mode() {mode = (mode == ANTENNA)? CABLE:ANTENNA;}
        void set_input() {input = (input == TV)? DVD:TV;}
        void setttings() const;
};

inline bool Remote::volup(Tv& t) { return t.volup();}
inline bool Remote::voldown(Tv& t) { return t.voldown();}
inline void Remote::onoff(Tv& t) { return t.onoff();}
inline void Remote::chanup(Tv& t) { return t.chanup();}
inline void Remote::chandown(Tv& t) { return t.chandown();}
inline void Remote::set_mode(Tv& t) {t.set_mode();}
inline void Remote::set_input(Tv& t) {t.set_input();}
inline void Remote::set_chan(Tv& t, int c) {t.channel = c;}