#include "10_10_5.h"

int main(){
    Stack<customer> st(3);
    char s1[] = "fangsen";
    char s2[] = "lvyilin";
    char s3[] = "hhh";
    for(int i=0;i<3;i++){
        if(i == 0) st.push(customer(s1, 10));
        else if(i == 1) st.push(customer(s2, 10.35));
        else st.push(customer(s3, 78.2));
        std::cout << st.size() << std::endl;
        std::cout << st.top().getFullname() << std::endl;
        std::cout << st.top().getPayment() << std::endl;
        std::cout << st.isFull() << std::endl;
        std::cout << "\n";
    }
    while(st.size()){
        std::cout << st.size() << std::endl;
        std::cout << st.top().getFullname() << std::endl;
        std::cout << st.top().getPayment() << std::endl;
        st.pop();
    }
    return 0;
    
    
}