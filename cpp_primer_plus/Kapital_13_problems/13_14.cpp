#include <iostream>
#include <string>
// 以下程序有什么问题

class Kitchen{
    private:
        double kit_sq_ft;
    protected:
        double kitArea(){
            return kit_sq_ft;
        }
    public:
        Kitchen(){ kit_sq_ft = 0; }
        virtual double area() {
            return kit_sq_ft * kit_sq_ft;
        }
};

class House: public Kitchen{
    private:
        double all_sq_ft = 120;
    public:
    House() { all_sq_ft += kitArea(); }
    double area(const char* s) const{
        std::cout << s << std::endl;
        return all_sq_ft;
    }
};

int main(){
    Kitchen* pkit = new Kitchen();
    std::cout << pkit->area() << std::endl;
    House* ph = new House();
    std::cout << ph->area("hh") << std::endl;
    std::cout << ph->Kitchen::area() << std::endl;
    return 0;
}