#include <iostream>
#include <string>

/**
 * 上行转换（子类到父类）和下行转换（父类到子类)
 * static_cast关键字
 * static_cast 只能用于良性转换，这样的转换风险较低，一般不会发生什么意外
 * 1.原有的自动类型转换，例如 short 转 int、int 转 double、const 转非 const、向上转型等
 * 2.void 指针和具体类型指针之间的转换，例如void *转int *、char *转void *等
 * 3.有转换构造函数或者类型转换函数的类与其它类型之间的转换，例如 double 转 Complex（调用转换构造函数）、Complex 转 double（调用类型转换函数)
 * */

class Complex {
    private:
        double m_real;
        double m_image;
    public:
        explicit Complex(double real = 0, double image  = 0): m_real(real),
                                                            m_image(image) {}
        operator double() const {
            return m_real;
        }
};


/**
 * dynamic_castynamic_cast 用于在类的继承层次之间进行类型转换，它既允许向上转型（Upcasting），也允许向下转型（Downcasting）
 * 向上转型是无条件的，不会进行任何检测，所以都能成功；向下转型的前提必须是安全的，要借助 RTTI 进行检测，所有只有一部分能成功
 * dynamic_cast 只能转换指针类型和引用类型，其它类型（int、double、数组、类、结构体等）都不行
 * */


class Base {
    protected:
        int m_a;
    public:
        explicit Base(int a = 0): m_a(a) {}
        int get_a() const { return m_a; }
        virtual void func() {}
};

class Derived: public Base {
    private:
        int m_b;
    public:
        explicit Derived(int a = 0, int b = 0): Base(a),
                                                m_b(b) {}
        int get_b() const { return m_b; }
};

class A {
    public:
        virtual void func() const {
            std::cout << "Class A" << std::endl;
        }
    private:
        int m_a;
};

class B: public A {
    public:
        virtual void func() const {
            std::cout << "Class B" << std::endl;
        }
    private:
        int m_b;
};

class C: public B {
    public:
        virtual void func() const {
            std::cout << "Class C" << std::endl;
        }
    private:
        int m_c;
};

class D: public C {
    public:
        virtual void func() const{
            std::cout << "Class D" << std::endl;
        }
    private:
        int m_d;
};


/**
 * reinterpret_cast关键字
 * reinterpret这种转换仅仅是对二进制位的重新解释，不会借助
 * 已有的规则对数据进行调整，非常简单粗暴，高风险
 * 同样一块内存，计算机会根据指针类型的不同，对内存进行不同类型的解释
 * reinterpret_cast就是用来重新解释的
 * */



/**
 * const_cast关键字，用来去除底层const属性
 * */

int main() {
    int m = 100;
    Complex c(12.5, 23.0);
    long long n = static_cast<long long>(m);
    char ch = static_cast<char>(m);
    int* p1 = static_cast<int*>(malloc(10*sizeof(int)));
    void* p2 = static_cast<void*>(p1);
    double real = static_cast<double>(c);
    // double* p3 = static_cast<double*>(p1); 错误，不能在两个具体类型指针之间进行转换

    Derived* pd1 = new Derived(35, 78);
    Base* pb1 = dynamic_cast<Base*>(pd1);
    std::cout << "pd1 = " << pd1 << std::endl;
    std::cout << "pb1 = " << pb1 << std::endl;
    std::cout << pb1->get_a() << std::endl;
    pb1->func();

    int x = 100;
    Derived* pd2 = reinterpret_cast<Derived*>(&x);
    Base* pb2 = dynamic_cast<Base*>(pd2);
    std::cout << "pd2 = " << pd2 <<std::endl;
    std::cout << "pb2 = " << pb2 << std::endl;
    std::cout << pb2->get_a() <<std::endl;; //输出一个垃圾直=值
    // pb2->func();
    /**
     * d 指向的是整型变量 n，并没有指向一个 Derived 类的对象，在使用 dynamic_cast 进行类型转换时也没有检查这一点，
     * 而是将 pd 的值直接赋给了 pb（这里并不需要调整偏移量），
     * 最终导致 pb 也指向了 n。因为 pb 指向的不是一个对象，所以get_a()得不到 m_a 的值（实际上得到的是一个垃圾值），
     * pb2->func()也得不到 func() 函数的正确地址。
     * pb2->func()得不到 func() 的正确地址的原因在于，pb2 指向的是一个假的“对象”，它没有虚函数表，也没有虚函数表指针，
     * 而 func() 是虚函数，必须到虚函数表中才能找到它的地址。
     * */

    A* pa = new A();
    B* pb;
    C* pc;
    pb = dynamic_cast<B*>(pa);
    if(pb == NULL) {
        std::cout << "Downcasting failed.\n";
    } else {
        std::cout << "Downcasting successfully: A* to B*\n";
        pb->func();
    }
    pc = dynamic_cast<C*>(pa);
    if(pc == NULL) {
        std::cout << "Downcasting failed\n";
    } else {
        std::cout << "Downcasting successfully: A* to C*\n";
        pc->func();
    }

    pa = new D();
    pb = dynamic_cast<B*>(pa);
    if(pb == NULL) {
        std::cout << "Downcasting failed.\n";
    } else {
        std::cout << "Downcasting successfully: A* to B*\n";
        pb->func();
    }
    pc = dynamic_cast<C*>(pa);
    if(pc == NULL) {
        std::cout << "Downcasting failed.\n";
    } else {
        std::cout << "Downcasting successfully: A* to C*\n";
        pc->func();
    }


    char str[] = "fangsen123";
    float* pfloat = reinterpret_cast<float*>(str);
    std::cout << *pfloat << std::endl;
    int* p_com = reinterpret_cast<int*>(new Complex(12.3, 34.1));
    std::cout << *p_com << std::endl;

    int i = 10;
    double j = 2.34;
    int* pi = &i;
    double* pj = reinterpret_cast<double*>(pi);
    std::cout << *pj << std::endl;



    /**
     * 顶层const和底层const
     * We use the term top-level const to indicate that thepointer itself is a const. 
     * When a pointer can point to a const object, we refer tothat const as a low-level const.
     * */
    int num_a = 10;
    int num_b = 5;
    const int* p_a = &num_a; //底层const，表明p_a指向的内容，不能通过p_a来改变
    // *p_a = 2; 错误
    // const int* pa = &num_a可以看成 const int (*pa), const是用来修饰*pa的，也就是p_a指向的内容
    p_a = &num_b; //p_a可以指向别的
    std::cout << *p_a << std::endl;

    int* const p_b = &num_b; //顶层const
    *p_b = 17;
    // p_b = &num_a; 错误，const时用来修饰p_b的，p_b不能指向别的了

    const int k = 100;
    const int* p_k = &k;
    int* p_kk = const_cast<int*>(p_k);
    *p_kk = 101;
    std::cout << "k = " << k << std::endl;
    std::cout << "p_k = " << *p_k << std::endl;
    std::cout << "p_kk = " << *p_kk << std::endl;

    std::cout << &k <<std::endl;
    std::cout << p_k << std::endl;
    std::cout << p_kk << std::endl;
    /**
     * k所在的地址实际上已经被变更内容了，所以是101，但是由于k是常量，
     * 每次访问k，编译器在汇编阶段将k用字面常量代替，也就是100.所以
     * 会造成地址相同，但是值不同的假象
     * */

    //const_cast真正用法,就是去掉底层const属性，使得源数据可以被改变
    int y = 12;
    const int* p_y = &y;
    int* p_yy = const_cast<int*>(p_y);
    *p_yy = 90;
    std::cout << "m = " << y << std::endl;
    std::cout << "p_y = " << *p_y << std::endl;
    std::cout << "p_yy = " << *p_yy <<std::endl;

    std::cout << &y << std::endl;
    std::cout << p_y << std::endl;
    std::cout << p_yy << std::endl;
    return 0;
}