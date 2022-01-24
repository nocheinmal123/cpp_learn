#include "11_vector.h"
#include <cmath>
using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;

namespace VECTOR{
    const double Rad_to_deg = 45/atan(1.0);

    void Vector::set_mag(){
        mag = sqrt(x * x + y * y);
    }

    void Vector::set_ang(){
        if(x == 0 && y == 0){
            ang = 0;
        }
        else ang = atan2(y, x); 
    }

    // set x from polar coordinate
    void Vector::set_x(){
        x = mag * cos(ang);
    }

    // set y from polat coordinate
    void Vector::set_y(){
        y = mag * sin(ang);
    }

    Vector::Vector(){
        x = y = mag = ang = 0;
        mode = Mode::RECT;
    }

    Vector::Vector(double n1, double n2, Mode _mode){
        mode = _mode;
        if(mode == Mode::RECT){
            x = n1;
            y = n2;
            set_mag();
            set_ang();
        }
        else if(_mode == Mode::POL){
            mag = n1;
            ang = n2;
            set_x();
            set_y();
        }
        else{
            std::cout << "Incorrect 3rd atgument to Vector() -- ";
            std::cout << "Vector set to 0.\n";
            x = y = mag = ang = 0;
            mode = Mode::RECT;
        }
    }

    void Vector::reset(double n1, double n2, Mode _mode = Mode::RECT){
        mode = _mode;
        if(mode == Mode::RECT){
            x = n1;
            y = n2;
            set_mag();
            set_ang();
        }
        else if(mode == Mode::POL){
            mag = n1;
            ang = n2;
            set_x();
            set_y();
        }
        else{
            std::cout << "Incorrect 3rd atgument to Vector() -- ";
            std::cout << "Vector set to 0.\n";
            x = y = mag = ang = 0;
            mode = Mode::RECT;
        }
    }

    Vector::~Vector(){

    }

    void Vector::polar_mode(){
        mode = Mode::POL;
    }

    void Vector::rect_mode(){
        mode = Mode::RECT;
    }

    Vector Vector::operator+(const Vector& vec) const{
        return Vector(this->x + vec.x, this->y + vec.y);
    }

    Vector Vector::operator-(const Vector& vec) const{
        return Vector(this->x - vec.x, this->y - vec.y);
    }

    Vector Vector::operator*(int n) const{
        return Vector(n *  this->x, n * this->y);
    }

    Vector Vector::operator-(){
        return Vector(-this->x, -this->y);
    }

    Vector& Vector::operator++(){
        this->x ++;
        this->y ++;
        return *this;
    }

    Vector Vector::operator++(int n){
        Vector vec(*this);
        this->x++;
        this->y++;
        return vec;
    }

    Vector& Vector::operator--(){
        this->x--;
        this->y--;
        return *this;
    }

    Vector Vector::operator--(int n){
        Vector vec(*this);
        this->x--;
        this->y--;
        return vec;
    }

    std::ostream& operator<<(std::ostream& out, const Vector& vec){
        out << vec.x <<", " << vec.y;
    }
}