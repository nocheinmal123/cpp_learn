#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>

template<typename T, int n>
class ArrayTP;

template<typename T,int n> 
std::ostream& operator<<(std::ostream&, const ArrayTP<T, n>&);

template<typename T, int n>
class ArrayTP{
    private:
        T ar[n];
    public:
        ArrayTP() {
            std::cout << "default arraytp called.\n";
        };
        explicit ArrayTP(const T&);
        virtual T& operator[](int);
        virtual T operator[](int) const;
        ArrayTP(const ArrayTP&);
        ArrayTP(const T* arr);
        int arraySum() const;
        bool arrayInsert(int, const T&);
        friend std::ostream& operator<< <>(std::ostream&, const ArrayTP<T, n>&);
};

template<typename T, int n>
ArrayTP<T, n>::ArrayTP(const T& v){
    std::cout << "ArrayTP con called.\n";
    for(int i = 0; i < n; i++){
        ar[i] = v;
    }
}

template<typename T, int n>
T& ArrayTP<T, n>::operator[](int index){
    if(index < 0 || index >= n){
        std::cout << "Error in array limits: " << index << " is out of range.\n";
        std::exit(EXIT_FAILURE);
    }
    return ar[index];
}

template<typename T, int n>
T ArrayTP<T, n>::operator[](int index) const{
    if(index < 0 || index >= n){
        std::cout << "Error in array limits: " << index << " is out of range.\n";
        std::exit(EXIT_FAILURE);
    }
    return ar[index];
}

template<typename T, int n>
ArrayTP<T, n>::ArrayTP(const ArrayTP& src){
    // std::cout << "ghhhhh" << std::endl;
    for(int i = 0; i < n; i++) ar[i] = src.ar[i];
}

template<typename T, int n>
bool ArrayTP<T, n>::arrayInsert(int index, const T& item){
    if(index < 0 || index >= n) return false;
    else{
        ar[index] = item;
        return true;
    }
}


template<typename T, int n>
ArrayTP<T, n>::ArrayTP(const T* arr){
    for(int i = 0; i < n; i++){
        ar[i] = arr[i];
    }
    // std::cout << "fsdfsd" << std::endl;
}

template<typename T, int n>
std::ostream& operator<<(std::ostream& out, const ArrayTP<T, n>& src){
    for(int i=0;i<n;i++) out << src.ar[i] << " ";
    return out;
}

template<typename T, int n>
int ArrayTP<T, n>::arraySum() const{
    int sum = 0;
    for(int i = 0; i < n; i++) sum += ar[i];
    return sum;
}

template<typename T1_, typename T2_, int size_, template<typename T, int n> class Array = ArrayTP>
class Pair{
    private:
        Array<T1_, size_> valFirst_;
        Array<T2_, size_> valSecond_;
    public:
        Pair(){ std::cout << "Pair default con.\n"; }
        Pair(const T1_& valFirst, const T2_& valSecond);
        Pair(const T1_* valFirst, const T2_* valSecond):valFirst_(valFirst), valSecond_(valSecond){
            // std::cout << "con with ptr.\n";
        }
        Array<T1_, size_>& first();
        Array<T2_, size_>& second();
        Array<T1_, size_> first() const{
            return valFirst_;
        }
        Array<T2_, size_> second() const{
            return valSecond_;
        }
        ~Pair() {}
};

template<typename T1_, typename T2_, int size_, template<typename T, int n> class Array>
Pair<T1_,T2_, size_, Array>::Pair(const T1_& valFirst, const T2_& valSecond): valFirst_(valFirst), valSecond_(valSecond_){

}

template<typename T1_, typename T2_, int size_, template<typename T, int n> class Array>
Array<T1_, size_>& Pair<T1_, T2_, size_, Array>::first(){
    return valFirst_;
}

template<typename T1_, typename T2_, int size_, template<typename T, int n> class Array>
Array<T2_, size_>& Pair<T1_, T2_, size_, Array>::second(){
    return valSecond_;
}

template <typename T1_, typename T2_, int n_ = 100>
class Wine{
    private:
        std::string Name_;
        int num_year_;
        Pair<T1_, T2_, n_, ArrayTP> Info_;
    public:
        Wine() {}
        Wine(const std::string& Name, int num_year, const int yr[], const int bot[]):Name_(Name),num_year_(num_year),Info_(yr, bot){
        }
        Wine(const std::string& Name, int num_year):Name_(Name), num_year_(num_year){

        }
        void Getbottles();
        void Wine_print() const{
            std::cout << Info_.first() << std::endl;
            std::cout << Info_.second() << std::endl;
        }
        int sum() const;
};

template<typename T1_, typename T2_, int n_>
void Wine<T1_, T2_, n_>::Getbottles(){
    std::cout << "The num of years is " << num_year_ << std::endl;
    std::cout << "Enter the years please: " << std::endl;
    for(int i = 0; i < n_; i++){
        int year;
        std::cin >> year;
        Info_.first().arrayInsert(i, year);
    }
    std::cout << "Enter the bottles please: " << std::endl;
    for(int i = 0; i < n_; i++){
        int bottle;
        std::cin >> bottle;
        Info_.second().arrayInsert(i, bottle);
    }
}

template<typename T1_, typename T2_, int n_>
int Wine<T1_, T2_, n_>::sum() const{
    return Info_.second().arraySum();
}

int main(){
    int yr[] = {1993, 1982, 1940};
    int bot[] = {10, 3, 21};
    Wine<int, int, 4> mywine("fangsen",4 , yr, bot);
    mywine.Wine_print();
    Wine<int, int, 2> wine2("lvyi lin", 2);
    wine2.Getbottles();
    wine2.Wine_print();
    std::cout << "Sum of bottles is: " << wine2.sum() << std::endl;
    return 0;
}