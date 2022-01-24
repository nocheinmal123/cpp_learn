#include <string>
#include <string.h>
#include <iostream>
#include <memory>

template<typename Type>
class Node{
    public:
        Type val;
        std::shared_ptr<Node> next;
        Node(const std::string _val = "default name"):val(_val){
            next = nullptr;
        }
        ~Node(){

        }
        Node(const Node& src){
            std::cout << "copy con called.\n";
            val = src.val;
            next = src.next; 
        }
        Node(Node&& src){
            std::cout << "move copy con called.\n";
            val = src.val;
            next = src.next;
            src.next = nullptr;
        }
        Node& operator=(const Node& src){
            val = src.val;
            next = src.next;
            return *this;
        }
};

template<typename Type>
class List{
    private:
        std::shared_ptr<Node<Type>> head;
        int len;
        int size;
    public:
        List(int _len):len(_len){
            size = 0;
            head = std::make_shared<Node<Type>>();
        }
        ~List(){
        }
        bool insertNode(std::shared_ptr<Node<Type>>& item){
            if(size < len){
                size++;
                item->next = head->next;
                head->next = item;
                return true;
            }
            return false;
        }
        bool insertNode(std::shared_ptr<Node<Type>>&& item){
            if(size < len){
                size++;
                item->next = head->next;
                head->next = item;
                return true;
            }
            return false;
        }
        bool deleteNode(const Node<Type>& item){
            std::shared_ptr<Node<Type>> ptr(head);
            bool flag = false;
            while(ptr->next != nullptr){
                if((ptr->next)->val == item.val){
                    std::shared_ptr<Node<Type>> temp = ptr->next;
                    ptr->next = temp->next;
                    flag = true;
                }
                ptr = ptr->next;
            }
            return flag;
        }
        bool deleteNode(std::shared_ptr<Node<Type>>&& item){
            std::shared_ptr<Node<Type>> ptr(head);
            bool flag = false;
            while(ptr->next != nullptr){
                if((ptr->next)->val == item->val){
                    std::shared_ptr<Node<Type>> temp = ptr->next;
                    ptr->next = temp->next;
                    flag = true;
                }
                ptr = ptr->next;
            }
            return flag;
        }
        void showList(){
            std::shared_ptr<Node<Type>> ptr(head);
            while(ptr != nullptr){
                if(ptr == head) {
                    ptr = ptr->next;
                    continue;
                }
                std::cout << "val = " << ptr->val << std::endl;
                ptr = ptr->next;
            }
        }
};