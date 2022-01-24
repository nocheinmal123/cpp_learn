#include "13_tabtenn0.h"

int main(){
    TableTennisPlayer player1("Chunk", "Blizzard", true);
    TableTennisPlayer player2("Tara", "Boomdea", false);
    player1.Name();
    if(player1.HasTable()){
        std::cout << ": has a table.\n";
    }
    else{
        std::cout << ": hasn't a table.\n";
    }
    player2.Name();
    if(player2.HasTable()){
        std::cout << ": has a table.\n";
    }
    else{
        std::cout << ": hasn't a table.\n";
    }

    RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
    rplayer1.Name();
    std::cout << "; Rating: " << rplayer1.Rating() << std::endl;
    RatedPlayer rplayer2(1212, rplayer1);
    rplayer2.Name();
    std::cout << "; Rating: " << rplayer2.Rating() << std::endl;

    // 基类对象初始化为派生类对象（用派生类初始化基类）
    RatedPlayer olaf1(1840, "Olaf", "Loaf", true);
    TableTennisPlayer olaf2(olaf1);
    // 要初始化olaf2,匹配的的构造函数原型如下：
    // TableTennisPlayer(const RatedPlayer&);
    // 但是在类定义中并没有这种构造函数，但是由于基类的引用可以指向一个派生类
    // 因此实际上将调用
    // TableTennisPlayer(const TableTennisPlayer&);
    // 同样地还有如下：
    // TableTennisPlayer winner;
    // winner = olaf1;
    // 这时，程序将使用隐式重载赋值运算符,将olaf1的基类部分赋值给winner
    // TableTennisPlayer& operator=(const TableTennisPlayer&) const;
    return 0;
}