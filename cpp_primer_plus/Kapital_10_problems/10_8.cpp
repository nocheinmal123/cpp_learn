#include "10_8_Node.h"

int main(){
    // Node node1("fangsen");
    // std::cout << node1.val << std::endl;
    // Node node2 = node1;
    // std::cout << node2.val << std::endl;
    // Node node3(node2);
    // std::cout << node3.val << std::endl;


    List<std::string>list(10);
    list.insertNode(std::move(std::shared_ptr<Node<std::string>>(new Node<std::string>("hhhh"))));
    list.insertNode(std::move(std::shared_ptr<Node<std::string>>(new Node<std::string>("fangsen"))));
    list.insertNode(std::move(std::shared_ptr<Node<std::string>>(new Node<std::string>("lvyilin"))));
    list.insertNode(std::move(std::shared_ptr<Node<std::string>>(new Node<std::string>("lll"))));
    list.showList();
    std::cout << std::endl;

    list.deleteNode(std::move(std::shared_ptr<Node<std::string>>(new Node<std::string>("fangsen"))));
    list.showList();
    std::cout << std::endl;
    list.deleteNode(std::move(std::shared_ptr<Node<std::string>>(new Node<std::string>("lll"))));
    list.showList();
    std::cout << std::endl;
    Node<std::string>node1("lvyilin");
    list.deleteNode(node1);
    list.showList();
    return 0;
}