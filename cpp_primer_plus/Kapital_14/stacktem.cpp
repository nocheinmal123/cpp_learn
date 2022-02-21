#include "stacktp.h"

class Node{
    private:
        int val;
    public:
        explicit Node(int v = 0):val(v){

        }
        void Show() const{
            std::cout << "val = " << val << std::endl;
        }
        Node& operator=(const Node& src){
            std::cout << "reload of =" << std::endl;
            val = src.val;
            return *this;
        }
        Node& operator=(Node&& src){
            std::cout << "move reload of =" << std::endl;
            val = src.val;
            return *this;
        }
        ~Node(){}
};

int main(){
    Stack<Node> s(10);
    for(int i=0;i<5;i++){
        s.push(Node(i));
        s.top().Show();
    }
    while(s.size()){
        s.top().Show();
        s.pop();
    }
    Stack<char*> s_p(10);
    char s1[] = "dasfasdf";
    char s2[] = "ii ooo ";
    char s3[] = "fangsen";
    s_p.push(s1);
    std::cout << s_p.top() << std::endl;
    std::cout << s_p.size() << std::endl;
    
    return 0;
}