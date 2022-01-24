#include "13_tabtenn0.h"

TableTennisPlayer::TableTennisPlayer(const std::string& fn, const std::string& ln, bool ht):firstname(fn),lastname(ln),hasTable(ht){

}

// 如果不使用列表初始化，而使用下面这种形式进行初始化
// 那么首先将为firstname调用默认构造函数（类定义中只是声明，这里才是做初始化）
// 然后再调用string类的赋值运算符，而用初始化列表可以节省一个步骤
// 直接使用了string的复制构造函数
// TableTennisPlayer::TableTennisPlayer(const std::string& fn, const std::string& ln, bool ht){
//     firstname = fn;
//     lastname = ln;
//     hasTable = ht;
// }

void TableTennisPlayer::Name() const{
    std::cout << lastname << ", " << firstname;
}

bool TableTennisPlayer::HasTable() const{
    return hasTable;
}

void TableTennisPlayer::ResetTable(bool v){
    hasTable = v;
}

RatedPlayer::RatedPlayer(unsigned int _r, const std::string &fn, const std::string &ln, bool ht):TableTennisPlayer(fn, ln, ht),rating(_r){

}

RatedPlayer::RatedPlayer(unsigned int _r, const TableTennisPlayer& tp):TableTennisPlayer(tp),rating(_r){

}

unsigned int RatedPlayer::Rating() const{
    return rating;
}

void RatedPlayer::ResetRating(unsigned int _rating){
    rating = _rating;
}