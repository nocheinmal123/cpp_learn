#include <iostream>
#include <string.h>
#include <string>

class Person{
    private:
        std::string fullname_;
        int age_;
    protected:
        void info_() const;
    public:
        explicit Person(const std::string& fullname = "no one", int age = 18);
        virtual ~Person();
        virtual void Show() const = 0;
        virtual void Set() = 0;
};

void Person::info_() const{
    std::cout << "fullname: " << fullname_ << std::endl;
    std::cout << "age: " << age_ << std::endl;
}

Person::Person(const std::string& fullname, int age): fullname_(fullname), age_(age){

}

Person::~Person(){

}

class Gunslinger: virtual public Person{
    private:
        double shoot_time_;
        int num_;
    public:
        Gunslinger(const std::string& fullname = "no one", int age = 18, double shoot_time = 1.3, int num = 15);
        Gunslinger(const Person&, double shoot_time = 1.3, int num = 18);
        Gunslinger(const Gunslinger&);
        virtual void Show() const override;
        virtual void Set() override;

};

Gunslinger::Gunslinger(const std::string& fullname, int age, double shoot_time, int num):Person(fullname, age), shoot_time_(shoot_time), num_(num){

}

Gunslinger::Gunslinger(const Person& person, double shoot_time, int num): Person(person), shoot_time_(shoot_time), num_(num){

}

Gunslinger::Gunslinger(const Gunslinger& src){
    shoot_time_ = src.shoot_time_;
    num_ = src.num_;
}

void Gunslinger::Show() const{
    Person::info_();
    std::cout << "shoot_time: " << shoot_time_ << std::endl;
    std::cout << "num: " <<num_ << std::endl;
}

void Gunslinger::Set(){
    std::cout << "Enter the shoot time pls: ";
    std::cin >> shoot_time_;
    std::cout << "Enter the num pls: ";
    std::cin >> num_;
}

template <typename T_>
void showCard(const T_&);

template <typename T1_, typename T2_>
class Card{
    private:
        T1_ suit_;
        T2_ val_;
    public:
        Card() = default;
        Card(T1_ suit, T2_ val): suit_(suit), val_(val) { std::cout << "con called.]\n"; }
        Card(const Card<T1_, T2_>&);
        virtual ~Card() {}
        // friend void showCard<Card<T1_, T2_> >(const Card<T1_, T2_>&);
        friend void showCard<>(const Card<T1_, T2_>&); //等价于上面那个
};

template <typename T_>
void showCard(const T_& src){
    std::cout << "suit: " << src.suit_ << std::endl;
    std::cout << "val: " << src.val_ << std::endl;
}

template <typename T1_, typename T2_>
Card<T1_, T2_>::Card(const Card<T1_, T2_>& src){
    suit_ = src.suit_;
    val_ = src.val_;
    std::cout << "copy con called.\n";
}


template <typename T1_, typename T2_>
class Pokerplayer: virtual public Person, private Card<T1_, T2_>{
    private:
        int year_;
    public:
        Pokerplayer() = default;
        Pokerplayer(const std::string& fullname, int age, int year, T1_ suit, T2_ val): Person(fullname, age), year_(year), Card<T1_, T2_>(suit, val){

        }
        Pokerplayer(const Person& person, int year, T1_ suit, T2_ val): Person(person), year_(year), Card<T1_, T2_>(suit, val){

        }
        Pokerplayer(const Person& person, int year, const Card<T1_, T2_>& card): Person(person), year_(year), Card<T1_, T2_>(card){

        }
        Pokerplayer(const Pokerplayer& src): Card<T1_, T2_>((const Card<T1_, T2_>&) src){
            year_ = src.year_;
        }
        virtual ~Pokerplayer() {}
        virtual void Show() const{
            Person::info_();
            showCard(((const Card<T1_, T2_>&) *this));
            std::cout << "year: " << year_ << std::endl;
        }
        virtual void Set(){
            std::cout << "Enter the year please:" ;
            std::cin >> year_;
        }
};

template<typename T1_, typename T2_, template <typename T1__, typename T2__> class TYPE = Card>
class Pokerman{
    private:
        TYPE<T1_, T2_> card;
    public:
        Pokerman() = default;
        /*
        封闭类采用 成员名(参数)的方法进行初始化
        私有继承采用 父类型名(参数)的方法进行初始化
        公有继承采用 父类构造函数名(参数)的方法

        其实继承，不管私有还是公有继承，调用都是父类名字，只是非模板类，父类名字和构造函数名一样儿
        但是模板类父类名多了<...>，其实本质都是调用父类名而非构造函数名字
        */
        Pokerman(const TYPE<T1_, T2_>& src): card(src){

        }
        Pokerman(const T1_& par1, const T2_& par2): card(par1, par2){

        }
        ~Pokerman() {}
        void Show() const{
            showCard(card);
        }
};

template<typename T1_, typename T2_>
class BadDude: public Gunslinger, public Pokerplayer<T1_, T2_>{
    private:
        int badLvL_;
    public:
        BadDude(const std::string& fullname, int age, int shoot_time, int num, int year, T1_ suit, T2_ val, int badlvl): Person(fullname, age), Gunslinger(fullname, age, shoot_time, num), Pokerplayer<T1_, T2_>(fullname, age, year, suit, val){
            badLvL_ = badlvl;
        }
        BadDude(const Gunslinger& gunslinger, int year, T1_ suit, T2_ val, int badlvl): Person(gunslinger), Gunslinger(gunslinger), Pokerplayer<T1_, T2_>(gunslinger, year, suit, val){
            badLvL_ = badlvl;
        }
        BadDude(const Pokerplayer<T1_, T2_>& pokerplayer, int shoot_time, int num, int year, T1_ suit, T2_ val, int badlvl):Person(pokerplayer), Gunslinger(pokerplayer, shoot_time, num), Pokerplayer<T1_, T2_>(pokerplayer){
            badLvL_ = badlvl;
        }
        BadDude(const Person& person, int shoot_time, int num, int year, T1_ suit, T2_ val, int badlvl): Person(person), Gunslinger(person, shoot_time, num), Pokerplayer<T1_, T2_>(person, year, suit, val){
            badLvL_ = badlvl;
        }
        virtual ~BadDude() {}
        virtual void Show() const{
            Gunslinger::Show();
            Pokerplayer<T1_, T2_>::Show();
            std::cout << "badLvL: " << badLvL_ << std::endl;
        }
        virtual void Set(){
            std::cout << "Enter the badlelvel pleas:" << std::endl;
            std::cin >> badLvL_;
        }
};



int main(){
    // Card<int, double> card2(11, 5.6);
    // BadDude<int, double> bad("fangsen", 30, 3, 34, 5, 13, 3.4, 7);
    // bad.Show();
    // Gunslinger gunsliner("lvyi lin", 21, 1.3, 16);
    // BadDude<int, double> bad2(gunsliner, 2, 1, 12.21, 6);
    // bad2.Show();

    Pokerman<double, double> p(3.5, 1.2);
    p.Show();
    return 0;
}