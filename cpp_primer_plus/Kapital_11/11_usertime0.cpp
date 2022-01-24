#include "11_mytime0.h"

int main(){
    using std::cout;
    using std::endl;
    Time planning;
    Time coding(2, 40);
    Time fixing(5, 55);

    cout << "planning time = ";
    planning.Show();
    cout << endl;

    cout << "coding time = ";
    coding.Show();
    cout << endl;

    cout << "fixing time = ";
    fixing.Show();
    cout << endl;

    Time total = coding.Sum(fixing);
    cout << "Total(coding + fixing) = ";
    total.Show();
    cout << endl;

    Time total2 = coding.operator+(fixing); // function notatin
    cout << "Total2 = ";
    total2.Show();
    cout << endl;

    Time total3 = coding + fixing;          // operator notation
    cout << "Total3 = ";
    total3.Show();
    cout << endl;

    /*
    Time t1,t2,t3,t4;
    t4 = t1 + t2 + t3; //valid?
    +是从左往右结合的运算符，因此，上面这句话会首先被转换成下面这样
    t4 = t1.oparator + (t2 + t3)；
    然后，函数参数 t2 + t3本身会被转换成一个函数调用
    t4 = t1.operatpr + (t2.operator + (t3))；
    t2.operator+(t3)返回一个Time对象，然后该对象作为函数
    t1.operator+的参数，最后再返回该对象和t1相加的新的Time对象
    给t4，完成计算 
    */

    Time minus = fixing - coding;
    minus.Show();

    Time mult = coding * 12;
    mult.Show();

    std::cout << "reaload ++ -- operations:" << std::endl;
    ++mult;
    mult.Show();

    minus++;
    minus.Show();

    coding--;
    coding.Show();

    --fixing;
    fixing.Show();

    std::cout << "Vergleich coding and fixing: " << (coding <= fixing) << std::endl;
    std::cout << coding << std::endl;

    Time temp;
    std::cin >> temp;
    std::cout << "temp: " << temp << std::endl;

    temp = 5*temp;
    std::cout << temp << std::endl;
    return 0;
}