#include <iostream>
#include <string>

/*
默认类型模板参数
template<typename T1, typename T2 = int>
虽然可以为类模板类型参数提供默认值，但不能为函数模板参数提供默认值
然后，可以为非类型参数提供默认值，这是对类模板和函数模板都是适用的
*/
template<typename T1, typename T2>
class Pair{
    private:
        T1 val_1;
        T2 val_2;
    public:
        T1& first();
        T2& second();
        T1 first() const { return val_1;}
        T2 second() const { return val_2;}
        Pair(const T1& val1, const T2& val2):val_1(val1),val_2(val2) {}
        Pair() {}
};

template<typename T1, typename T2>
T1& Pair<T1, T2>::first(){
    return val_1;
}

template<typename T1, typename T2>
T2& Pair<T1, T2>::second(){
    return val_2;
}


/*
显式具体化
explicit specialization

*/

// partial specialization
// general template
template<typename T1, typename T2>
class Sample{

};

// full specialization
template<>
class Sample<int, int>{

};

// partial specialization
// specialzation with T2 set to int
template<typename T1>
class Sample<T1, int>{

};


// general template
template<class T1, class T2, class T3> class Trio{};

// specialization with T2 set to T2
template<class T1, class T2>
class Trio<T1, T2, T2>{};

// specizalization with T3 and T2 set to T1*
template<class T1> 
class Trio<T1, T1*, T1*>{};


int main(){
    Pair<std::string, int> a("kkkk", 3);
    Pair<std::string, int> rating[4] = {
        Pair<std::string, int>("The Purpled Duck", 5),
        Pair<std::string, int>("Jaquie's Frisco Al Fresco", 4),
        Pair<std::string, int>("Cafe Souffle", 5),
        Pair<std::string, int>("Bertie's Eats", 3)
    };
    for(int i = 0; i<4; i++){
        std::cout << rating[i].first() << ", " << rating[i].second() << std::endl;
    }
    rating[0].first() = "fangsen";
    rating[0].second() = 90;
    std::cout << rating[0].first() << ", " << rating[0].second() << std::endl;

    Trio<int, short, char*> t1; // use general
    Trio<int, char, char> t2; // use Trio<T1, T2, T2>
    Trio<char, char*, char*> t3; // use Trio<T1, T1*, T1*>
    return 0;
}

