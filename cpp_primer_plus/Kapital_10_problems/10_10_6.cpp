#include "10_10_6.h"

Move::Move(double _x, double _y):x(_x),y(_y){

}

Move::~Move(){

}

void Move::showMove() const{
    std::cout << "x = "<< x << ", " << "y = " << y << std::endl;
}

Move&& Move::add(const Move& m) const{
    return std::move(Move(x + m.x, y + m.y));
}

// Move& Move::add(const Move& m) const{
//     return Move(x + m.x, y + m.y);
// } 非const引用需要返回一个左值，但是这里返回的是临时变量，是个右值

void Move::reset(double _x, double _y){
    x = _x;
    y = _y;
}


