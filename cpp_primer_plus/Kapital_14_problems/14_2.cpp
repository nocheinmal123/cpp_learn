#include <iostream>
#include <string>
#include <string.h>

class Frabjous{
    private:
        std::string fab;
    public:
        Frabjous(const std::string& s = "C++"): fab(s) {}
        Frabjous(const Frabjous& f){
            std::cout << "copy con called.\n";
            fab = f.fab;
        }
        virtual void tell() {
            std::cout << "fab = " << fab << std::endl;
        }
};

class Gloam{
    private:
        int glip;
        Frabjous fb;
    public:
        Gloam(int g = 0, const std::string& s = "C++"): glip(g), fb(s) {}
        Gloam(int g, Frabjous& f):glip(g), fb(f) {}
        void tell(){
            fb.tell();
            std::cout << "glip = " << glip << std::endl;
        }
};

int main(){
    Frabjous f("lllll");
    Gloam g(10,"fangsen");
    Gloam h(90,f);
    g.tell();
    h.tell();
    return 0;
}