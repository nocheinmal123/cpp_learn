#include <iostream>
#include <string>
#include <string.h>

namespace VECTOR{
    enum class Mode{
        RECT,
        POL,
    };
    class Vector{
        private:
            double x;       //horizontal value
            double y;       //vertical value
            double mag;     //length of vector
            double ang;     //direction of vector in degrees
            Mode mode;
        // private methods for settting values
            void set_mag();
            void set_ang();
            void set_x();
            void set_y();
        public:
            Vector();
            Vector(double _x, double _y, Mode _mode = Mode::RECT);
            void reset(double _x, double _y, Mode _mode = Mode::RECT);
            ~Vector();
            double xval() const {return x;}
            double yval() const {return y;}
            double magval() const {return mag;}
            double angval() const {return ang;}
            void polar_mode();
            void rect_mode();
        // operator overloading
            Vector operator+(const Vector& vec) const;
            Vector operator-(const Vector& vec) const;
            Vector operator*(int n) const;
            Vector operator-();     //reverse assignment
            Vector& operator--();
            Vector operator--(int);
            Vector& operator++();
            Vector operator++(int);
        // friends
            friend Vector operator*(int n, const Vector& vec);
            friend std::ostream& operator<<(std::ostream& out, const Vector& vec);
    };
}