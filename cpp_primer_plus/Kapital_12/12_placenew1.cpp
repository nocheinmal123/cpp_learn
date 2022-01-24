#include <iostream>
#include <string>
#include <string.h>
#include <new>
const int BUF = 512;

class JustTesting{
    private:
        std::string words;
        int number;
    public:
        JustTesting(const std::string& s = "Just Testing", int n = 0){
            words = s;
            number = n;
            std::cout << "constructed.\n";
        }
        ~JustTesting(){
            std::cout << "destroyed.\n";
        }
        void Show(){
            std::cout << words << ", " << number << std::endl;
        }
};

int main(){
    char* buffer = new char[BUF]; // get a block of memory
    JustTesting* pc1, *pc2;
    pc1 = new(buffer) JustTesting; // place obj in buffer
    pc2 = new JustTesting("Heap1", 20); // place obj on heap
    std::cout << "Memory block addresse:\n" << "buffer: " << (void*)buffer << " heap: " << pc2 << std::endl;
    std::cout << pc1 << ": ";
    pc1->Show();
    std::cout << pc2 << ": ";
    pc2->Show();

    JustTesting *pc3, *pc4;
    // pc3 = new(buffer) JustTesting("Bad", 3); 
    // pc3 相对于pc1的偏移量为JustTesting对象的大小
    // 所以应该用下面这种写法
    pc3 = new(buffer + sizeof(JustTesting)) JustTesting("Bad", 3);
    pc4 = new JustTesting("Heap2", 10);
    std::cout << "Memory contents:\n";
    std::cout << pc3 << ": ";
    pc3->Show();
    std::cout << pc4 << ": ";
    pc4->Show();

    // delete pc1; delete无法与定位new运算符配合使用，因为比如pc3平没有接受到
    // delete pc3; new运算符返回的地址，此时delete会导致错误
    // 但是buffer是用new来初始化的，因为必须用delete(delete[])来释放
    pc3->~JustTesting(); //使用定位new，一定要显式地调用析构函数来释放内存
    pc1->~JustTesting(); //同时要注意，仅当所有对象都被销毁后，才能释放用于储存这些对象的缓冲区
    delete pc2;
    delete pc4;
    delete[] buffer;
    std::cout << "Done.\n";
    return 0;
}