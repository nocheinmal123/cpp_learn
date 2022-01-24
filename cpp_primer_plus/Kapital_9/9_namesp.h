#include <string>
// create the pers and debts namesspcaes
namespace pers{
    // struct Person{
    //     std::string fname;
    //     std::string lname;
    // };
    // template <typename T>
    // void getPerson(T& p);
    // template <typename T>
    // void showPerson(const T& p);
    class Person{
        private:
            std::string fname;
            std::string lname;
        public:
            Person(){

            }
            Person(std::string _fname, std::string _lname):fname(_fname),lname(_lname){

            }
            ~Person(){

            }
            void setPerson();
            void showPerson() const;
    };
}

namespace debts{
    using namespace pers;
    // struct Debt{
    //     Person name;
    //     double amount;
    // };
    // void getDebt(Debt& debt);
    // void showDebt(const Debt& debt);
    // double sumDebt(const Debt* ar, int n);
    class Debt{
        private:
            Person name;
            double amount;
        public:
            Debt():name(){

            }
            Debt(std::string _fname, std::string _lname, double _amount):name(_fname, _lname), amount(_amount){

            }
            ~Debt(){

            }
            friend double sumDebt(const Debt* arr, int n);
            void setDebt();
            void showDebt() const;
    };
}