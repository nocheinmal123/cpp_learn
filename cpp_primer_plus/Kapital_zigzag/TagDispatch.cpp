#include <string>
#include <string.h>
#include <iostream>

struct NormalVersionTag {};
struct IntVersionTag {};

template <typename T_>
struct Dispatch {
    using Tag = NormalVersionTag;
};

template <>
struct Dispatch<int> {
    using Tag = IntVersionTag;
};

template <typename T1_, typename T2_>
void process(T1_ x, T2_ y, NormalVersionTag) {
    std::cout << "Normal Version.\n";
}

template <typename T1_, typename T2_>
void process(T1_ x, T2_ y, IntVersionTag) {
    std::cout << "Int Version.\n";
}

template <typename T1_, typename T2_>
inline void func(T1_ x, T2_ y) {
    process(x, y, typename Dispatch<T2_>::Tag {});
}

int main() {
    int a = 10;
    int b = 5;
    double x = 1.3;
    double y = 9.32;
    func(a, b);
    func(x, y);
    return 0;
}