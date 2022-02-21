#include <iostream>
#include <string>
#include <string.h>

template <typename T1_, typename T2_>
class Card;

template <typename T1_, typename T2_>
void showCard(const Card<T1_, T2_>&);

template <typename T1_, typename T2_>
class Card{
    private:
        T1_ suit_;
        T2_ val_;
    public:
        Card() = default;
        Card(T1_ suit, T2_ val): suit_(suit), val_(val) {}
        virtual ~Card() {}
        // friend void showCard<Card<T1_, T2_> >(const Card<T1_, T2_>&);
        friend void showCard<T1_, T2_>(const Card<T1_, T2_>&); //不能用上面那个，因为showcard需要两个参数
        // 所以具体化的时候也需要两个，可以跟14_7_4.cpp中的作对比，但是可以用下面这个,也就是说 <>在不同的时候
        // 表示的是不同意思，14_7_4.cpp中是<Card<T1_, T2_>>，这里是<T1_, T2_>
        // friend void showCard<>(const Card<T1_, T2_>&);
};

template <typename T1_, typename T2_>
void showCard(const Card<T1_, T2_>& src){
    std::cout << "suit: " << src.suit_ << std::endl;
    std::cout << "val: " << src.val_ << std::endl;
}

//  测试公有继承模板类 初始化函数写法
template <typename T1__, typename T2__>
class base{
    private:
        T1__ key_;
        T2__ val_;
    public:
        base() = default;
        base(const T1__& key, const T2__& val): key_(key), val_(val){

        }
        base(const base& src){
            key_ = src.key_;
            val_ = src.val_;
        }
        ~base() {}
};

template <typename T1_, typename T2_>
class derived: public base<T1_, T2_>{
    public:
        derived() = default;
        derived(const T1_& key, const T2_& val): base<T1_, T2_>(key, val){

        }
        ~derived() {}
};

int main(){
    Card<int, double> card(10,3.5);
    showCard(card);

    derived<int, double> d(5, 3.71);
    return 0;
}