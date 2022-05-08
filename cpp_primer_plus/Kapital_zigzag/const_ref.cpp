#include <iostream>
#include <string>
#include <memory>
class Base {
    private:
        int base_val_;
    public:
        Base(int& val): base_val_(val) {

        }
        ~Base() {}
};

class Derived: public Base {
    private:
        int derived_val_;
    public:
        Derived(int& derived_val, int& base_val): derived_val_(derived_val), Base(base_val) {}
        ~Derived() {}
};


class Sample {
    private:
        int val_;
        std::shared_ptr<Base> ptr_base_;
    public:
        Sample(int& val, std::shared_ptr<Base>& ptr_base): val_(val), ptr_base_(ptr_base){}
        ~Sample() {}
};


int main() {
    int k = 3, m = 5;
    Derived obj_derived(k, m);
    std::shared_ptr<Base> ptr = std::make_shared<Base>(k);
    Sample obj_sample(k, ptr);
    return 0;
}