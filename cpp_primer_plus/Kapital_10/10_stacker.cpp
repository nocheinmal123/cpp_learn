#include "10_stack.h"
#include <iostream>

int main(){
    Stack<char>st(1000);
    if(st.isEmpty()) std::cout << "st is empty.\n";
    st.push('A');
    std::cout << st.size() << std::endl;
    std::cout << st.top() << std::endl;
    st.push('H');
    std::cout << st.size() << std::endl;
    std::cout << st.top() << std::endl;
    if(st.pop()){
        std::cout << "After pop:" << std::endl;
        std::cout << st.top() << std::endl;
        std::cout << st.size() << std::endl;
    }
    st.pop();
    std::cout << st.size() << std::endl;

    std::cout << "------------------" << std::endl;
    Stack<double>sta(5);
    for(int i=0;i<6;i++){
        std::cout << sta.push(i + 1.3) << std::endl;
        std::cout << "top = " << sta.top() << std::endl;
        std::cout << "size = " << sta.size() << std::endl;
    }
    for(int i=0;i<6;i++){
        std::cout << sta.pop() << std::endl;
        std::cout << "top = " << sta.top() << std::endl;
        std::cout << "size = " << sta.size() << std::endl;
    }
    return 0;
}