#include <string>
#include <string.h>
#include <iostream>

class Move{
    private:
        double x;
        double y;
    public:
        Move(double a = 0, double b = 0);
        ~Move();
        void showMove() const;
        Move&& add(const Move& m) const;
        // Move& add(const Move& m) const;
        void reset(double a = 0, double b = 0);
};