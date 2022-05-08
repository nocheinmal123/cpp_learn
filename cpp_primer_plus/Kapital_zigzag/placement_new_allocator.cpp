#include <iostream>
#include <string>
#include <string.h>
#include <memory>
#include <memory.h>
#include <new>
#include <vector>


class Sample {
    private:
        int _m;
    public:
        Sample() = default;
        explicit Sample(int m): _m(m) {}
        int get_m() const {
            return _m;
        }
        ~Sample() {}
};

class Compelx {
    private:
        int _m;
        int _n;
    public:
        Compelx(int m, int n): _m(m),
                            _n(n) {}
        ~Compelx() {}
        void func() {
            std::cout << "m = " << _m << std::endl;
            std::cout << "n = " << _n << std::endl;
        }
        friend std::ostream& operator<<(std::ostream& out, const Compelx& src) {
            out << src._m << ", " << src._n;
            return out;
        }
};

void test_allocator() {
    /**
     * std::allocator是C++标准库中提供的默认分配器，
     * 我们在使用new来申请内存构造新的对象的时候，势必
     * 要生成对象，而使用std::allocator可以把内存分配
     * 和对象的构造这两部分逻辑分离开，使得内存是原始的
     * 未构造的
     * */
    std::vector<int> vec{1, 2, 3, 4, 5, 190};
    std::allocator<int> alloc;
    std::cout << vec.size() << std::endl;
    auto p = alloc.allocate(vec.size() * 2);
    /*uninitialized_copy(b, e, b2)
    从迭代器b和e指出的范围中拷贝元素到指定的未构造的内存中
    内存必须足够大，能容纳输入序列中元素的拷贝
    返回值指向最后一个构造的元素之后的位置
    */
    auto q = std::uninitialized_copy(vec.begin(), vec.end(), p);
    std::cout << *(q-1) << std::endl;

    /*
    从迭代器b开始，拷贝n个元素到指定的内存中
    uninitialized_copy_n(b, n, p)，返回值
    是最后一个构造的元素之后位置
    */
    auto q2 = std::uninitialized_copy_n(vec.begin(), 2, p);
   
    std::cout << *(q2 - 1) << std::endl;

    std::vector<Compelx> vec2{Compelx(12, 3), Compelx(78,100)};
    std::allocator<Compelx> alloc2;
    auto buff = alloc2.allocate(vec2.size() * 2);

    auto p_last = std::uninitialized_copy(vec2.begin(), vec2.end(), buff);
    // 剩下来的全部初始化为Complex(101, 780)
    auto p_last_last = std::uninitialized_fill_n(p_last, vec2.size(), Compelx(101, 780));
    for(int i = 0; i < vec2.size() * 2; i++) {
       std::cout << *(p_last - vec2.size() + i) << std::endl;
    }
}


int main() {
    Sample* p[5];
    char* mem = new char[5 * sizeof(Sample)];
    for(int i = 0; i < 5; i++) {
        p[i] = new (mem + i * sizeof(Sample))Sample(i);
    }
    for(int i = 0; i < 5; i++) {
        std::cout << p[i]->get_m() << std::endl;
    }
    for(int i = 0; i < 5; i++) {
        p[i]->~Sample();
    }
    delete[] mem;
    std::cout << "<========================>" << std::endl;
    char* buff = new char[5 * sizeof(Sample)];
    memset(buff, 0 , sizeof(buff));
    Sample* start = reinterpret_cast<Sample*>(buff); // 将mem的首地址赋值给一个Sample类的指针
    for(int i = 0; i < 5; i++) {
        new (start + i)Sample(i + 2);
        std::cout << (start + i)->get_m() << std::endl;
        (start + i)->~Sample();
    }

    delete[] buff;

    std::cout << "<======================>" << std::endl;
    Sample* p_sample = new Sample[10];
    for(int i = 0; i < 10; i++) {
        std::cout << p_sample[i].get_m() << std::endl;
        std::cout << (p_sample + i)->get_m() << std::endl;
    }
    std::cout << "<===============================>\n";
    delete[] p_sample;
    Sample** p_sample2 = new Sample*[10];
    for(int i = 0; i < 10; i++) {
    int* p_int = new int[10];
        p_sample2[i] = new Sample(7);
        std::cout << p_sample2[i]->get_m() << std::endl;
    }
    std::cout << "<==================================>\n";
    int** p_int = new int*[3];
    for(int i = 0; i < 3; i++) {
        p_int[i] = new int(12);
        std::cout << *p_int[i] << std::endl;
    }

    std::cout << "****************************************\n";
    std::allocator<Compelx> Myallocator;
    Compelx* arr =  Myallocator.allocate(5);
    for(int i = 0; i < 3; i++) {
        // 往内存里写入数据，利用构造函数
        Myallocator.construct(arr + i, Compelx(i, 2 * i + 1));//可以直接写构造函数作为参数
    }
    for(int i = 0; i < 3; i++) {
        std::cout << arr[i] << std::endl;
    }
    for(int i = 0; i < 3; i++) {
        // 调用析构函数，释放对象
        Myallocator.destroy(arr + i);
    }
    Myallocator.deallocate(arr, 5);

    test_allocator();
    return 0;
}