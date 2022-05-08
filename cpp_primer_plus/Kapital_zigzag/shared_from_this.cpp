#include <iostream>
#include <memory>

class Outer: public std::enable_shared_from_this<Outer> {
    private:
        int val_outer_;
        class Inner {
            private:
                int val_inner_;
                std::shared_ptr<Outer> sp_outer_;
            public:
                Inner(std::shared_ptr<Outer> sp_outer, int val_inner): sp_outer_(sp_outer), 
                                                                        val_inner_(val_inner) {

                }
        };
    public:
        Outer(int val_outer): val_outer_(val_outer) {

        }
        void pass_this_to_inner() {
            std::shared_ptr<Inner> sp_inner = std::make_shared<Inner>(shared_from_this(), 20);

        }
};

int main() {
    std::shared_ptr<Outer> sp_outer = std::make_shared<Outer>(101);
    sp_outer->pass_this_to_inner();
}