#include <iostream>
#include <string>
#include <string.h>

template <typename T_, int size_>
class Array;

template <typename T_, int size_>
std::ostream& operator<<(std::ostream&, const Array<T_, size_>&);

template <typename T_, int size_ = 10>
class Array{
    private:
        T_ ar[size_];
    public:
        Array() { std::cout << "array default con.\n"; }
        explicit Array(const T_&);
        Array(const Array&); //在类声明中可以采用Array，而不用Array<T_, size_>
        Array(const T_*);
        virtual T_& operator[](int);
        virtual T_ operator[](int) const;
        bool arrayInsert(int, const T_&);
        Array& operator=(const Array&);
        auto arraySum() const;
        friend std::ostream& operator<< <T_, size_>(std::ostream&, const Array&); //在类声明中采用Array, 而不是Array<T_, size_>
};


template <typename T_, int size_>
Array<T_, size_>::Array(const T_& item){
    for(int i = 0; i < size_; i++) ar[i] = item;
}

template <typename T_, int size_>
Array<T_, size_>::Array(const Array& src){
    std::cout << "copy con called.\n";
    for(int i = 0; i < size_; i++) ar[i] = src.ar[i];
}

template <typename T_, int size_>
Array<T_, size_>::Array(const T_* arr_ptr){
    for(int i = 0; i < size_; i++) ar[i] = arr_ptr[i];
}

template <typename T_, int size_>
T_& Array<T_, size_>::operator[](int index){
    return ar[index];
}

template <typename T_, int size_>
T_ Array<T_, size_>::operator[](int index) const{
    return ar[index];
}

template <typename T_, int size_>
bool Array<T_, size_>::arrayInsert(int index, const T_& item){
    if(index < 0 || index >=  size_) return false;
    else{
        ar[index] = item;
        return true;
    }
}

template<typename T_, int size_>
auto Array<T_, size_>::arraySum() const{
    T_ sum = 0;
    for(int  i = 0; i < size_; i++) sum += ar[i];
    return sum;
}

template<typename T_, int size_>
Array<T_, size_>& Array<T_, size_>::operator=(const Array& src){
    for(int i = 0; i < size_; i++) ar[i] = src.ar[i];
}

template <typename T_, int size_>
std::ostream& operator<<(std::ostream& out, const Array<T_, size_>& src){
    for(int i = 0; i < size_; i++) out << src.ar[i] << " ";
    return out;
}

// template <typename T_, int size_>
// class Pair: public Array<T_, size_>{
//     private:
//         using ArrayT = Array<T_, size_>;
//     public:
//         Pair() {}
//         Pair(const ArrayT& src):ArrayT(src){
//             // ArrayT::Array(src);
//         }
// };


template <typename T1_,typename T2_, int size_>
class Pair: private Array<T1_, size_>, private Array<T2_, size_>{
    private:
        using ArrayT1 = Array<T1_, size_>;
        using ArrayT2 = Array<T2_, size_>;
    public:
        Pair() = default;
        Pair(const ArrayT1&, const ArrayT2&);
        Pair(const T1_*, const T2_*);
        Pair(const Pair&);
        ArrayT1& first();
        ArrayT2& second();
        ArrayT1 first() const;
        ArrayT2 second() const;
};

template<typename T1_,typename T2_, int size_> //注意，使用私有继承的时候，列表初始化不是调用父类的构造函数
// 而直接是父类名(参数)
Pair<T1_, T2_, size_>::Pair(const Array<T1_, size_>& arr1, const Array<T2_, size_>& arr2):ArrayT1(arr1), ArrayT2(arr2){
}

template <typename T1_, typename T2_, int size_>
Pair<T1_, T2_, size_>::Pair(const T1_* arr1, const T2_* arr2):ArrayT1(arr1), ArrayT2(arr2){
}

template <typename T1_, typename T2_, int size_>
Pair<T1_, T2_, size_>::Pair(const Pair& src):ArrayT1(src.first()), ArrayT2(src.second()){

}

template<typename T1_,typename T2_, int size_>
Array<T1_, size_>& Pair<T1_, T2_, size_>::first(){
    // std::cout << "ref first" << std::endl;
    return (ArrayT1&) *this;
}

template<typename T1_, typename T2_, int size_>
Array<T2_, size_>& Pair<T1_, T2_, size_>::second(){
    // std::cout << "ref scecond " << std::endl;
    return (ArrayT2&) *this;
}

template <typename T1_, typename T2_, int size_>
Array<T1_, size_> Pair<T1_, T2_, size_>::first() const{
    // std::cout << "copy first.\n";
    return (ArrayT1)*this;
}

template <typename T1_, typename T2_, int size_>
Array<T2_, size_> Pair<T1_, T2_, size_>::second() const{
    // std::cout << "copy scecond.\n";
    return (ArrayT2)*this;
}

template <typename T1_, typename T2_, int size_ = 10>
class Wine: private Pair<T1_, T2_, size_>{
    private:
        std::string Name_;
        int num_years_;
    public:
        Wine() = default;
        Wine(const std::string& Name, int num_year): Name_(Name), num_years_(num_year), Pair<T1_, T2_, size_>(){}
        Wine(const std::string& Name, int num_years, Pair<T1_, T2_, size_>& pair_info):Name_(Name), num_years_(num_years), Pair<T1_, T2_, size_>(pair_info) {}
        Wine(const std::string&, int, Array<T1_, size_>&, Array<T2_, size_>&);
        Wine(const std::string&, int, T1_*, T2_*);
        auto getSum() const;
        void GetBottles();
};

template <typename T1_, typename T2_, int size_>
Wine<T1_, T2_, size_>::Wine(const std::string& Name, int num_years, Array<T1_, size_>& arT1, Array<T2_, size_>& arT2):Name_(Name), num_years_(num_years), Pair<T1_, T2_, size_>(arT1, arT2){

}

template <typename T1_, typename T2_, int size_>
Wine<T1_, T2_, size_>::Wine(const std::string& Name, int num_years, T1_* arr1, T2_* arr2):Name_(Name), num_years_(num_years), Pair<T1_, T2_, size_>(arr1, arr2){

}

template <typename T1_, typename T2_, int size_>
auto Wine<T1_, T2_, size_>::getSum() const{
    return ((Pair<T1_, T2_, size_>& ) *this).second().arraySum();
}

template <typename T1_, typename T2_, int size_>
void Wine<T1_, T2_, size_>::GetBottles(){
    std::cout << "The num of years is: " << num_years_ << std::endl;
    std::cout << "Enter the year of wine: " << std::endl;
    for(int i = 0; i < size_; i++){
        T1_ year;
        std::cin >> year;
        ((Pair<T1_, T2_, size_>&) *this).first().arrayInsert(i, year);
    }
    std::cout << "Enter the num of bottles: " << std::endl;
    for(int i = 0; i < size_; i++){
        T2_ bottle;
        std::cin >> bottle;
        ((Pair<T1_, T2_, size_>&) *this).second().arrayInsert(i, bottle);
    }
}

int main(){
    int year[] = {1990, 2019};
    int year2[] = {1990, 2022};
    double bot[] = {89.9, 109.12};
    Array<int, 2> arr1(year);
    Array<double ,2> arr2(bot);
    Pair<int, double, 2> pair1(arr1, arr2);
    Pair<int, double, 2> pair2(year, bot);
    // Pair<int, 2> pair(arr1);
    std::cout << pair1.first() << std::endl;
    std::cout << pair1.second() << std::endl;

    Array<int, 2> arr_1(pair1.first());
    std::cout << arr_1 << std::endl;

    pair1.first() = Array<int, 2>(year2);
    std::cout << pair1.first() << std::endl;

    Wine<int, double, 2> mywine("fangsen", 2, year, bot);
    std::cout << "sum = " << mywine.getSum() << std::endl;
    Wine<int, double, 5> mywine2("lvyi lin", 5);
    mywine2.GetBottles();
    std::cout << mywine2.getSum() << std::endl;
    return 0;
}