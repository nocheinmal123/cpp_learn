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

class Gloam: private Frabjous{
    private:
        int glip;
    public:
        Gloam(int g = 0, const std::string& s = "C++"): glip(g), Frabjous(s){}
        Gloam(int g, Frabjous& f):glip(g), Frabjous(f) {}
        void tell(){
            Frabjous::tell();
            std::cout << "glip = " << glip << std::endl;
        }
};

int main(){
    Gloam g(12, "kkkk");
    g.tell();
    return 0;
}
