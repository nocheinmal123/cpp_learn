#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <memory>

class Node{
    private:
        std::string value;
        std::shared_ptr<Node> pre;
        std::shared_ptr<Node> nxt;
    public:
        explicit Node(std::string v);
        ~Node();
        // std::shared_ptr<Node> getPre();
        // std::shared_ptr<Node> getNxt();
        void Print(){
            std::cout<<value<<std::endl;
            std::cout<<pre->value<<std::endl;
            std::cout<<nxt->value<<std::endl;
        }
        friend class DoubleLinkList;
};

Node::Node(std::string v):value(v){
    pre = nxt = nullptr;
}

// std::shared_ptr<Node> Node::getPre(){
//     return pre;
// }

// std::shared_ptr<Node> Node::getNxt(){
//     return nxt;
// }


Node::~Node(){

}

class DoubleLinkList{
    private:
        std::shared_ptr<Node> head;
        int size;
    public:
        DoubleLinkList();
        ~DoubleLinkList();
        bool insertNode(std::shared_ptr<Node> p_node);
        std::shared_ptr<Node> findNode(const std::string str);
        bool deleteNode(std::shared_ptr<Node>);
        void visitDLL();
};

DoubleLinkList::DoubleLinkList():head(new Node("head")){
    size = 0;
}

bool DoubleLinkList::insertNode(std::shared_ptr<Node> p_node){
    if(size == 0){
        head->nxt = p_node;
        p_node->pre = head;
        size++;
        return true;
    }
    std::shared_ptr<Node> temp_nxt = head->nxt;
    head->nxt = p_node;
    temp_nxt->pre = p_node;
    // std::cout<<head->nxt<<std::endl;
    // std::cout<<temp_nxt->nxt<<std::endl;
    p_node->pre = head;
    p_node->nxt = temp_nxt;
    size++;
    return true;
}

std::shared_ptr<Node> DoubleLinkList::findNode(const std::string str){
    std::shared_ptr<Node> _cur = head;
    while(_cur != nullptr){
        if(_cur->value == str) return _cur;
        _cur = _cur->nxt;
    }
    return nullptr;
}

bool DoubleLinkList::deleteNode(std::shared_ptr<Node> p_node){
    if(size == 0) return false;
    if(size == 1){
        head->nxt = nullptr;
        size--;
        return true;
    }
    std::shared_ptr<Node> temp_pre = p_node->pre;
    std::shared_ptr<Node> temp_nxt = p_node->nxt;
    temp_pre->nxt = temp_nxt;
    temp_nxt->pre = temp_pre;
    return true;
}

void DoubleLinkList::visitDLL(){
    std::shared_ptr<Node> _cur = head;
    std::cout<<"*******************"<<std::endl;
    while(_cur != nullptr){
        std::cout<<"element: "<<_cur->value<<std::endl;
        _cur = _cur->nxt;
    }
    std::cout<<"*******************"<<std::endl<<std::endl;
    return;
}

DoubleLinkList::~DoubleLinkList(){
    
}


int main(){
    std::shared_ptr<DoubleLinkList> DLL(new DoubleLinkList());
    std::shared_ptr<Node> p1(new Node("1"));
    DLL->insertNode(p1);
    std::shared_ptr<Node> p2(new Node("fangsen"));
    DLL->insertNode(p2);
    DLL->visitDLL();
    if(DLL->findNode("fangsen") ==  nullptr) std::cout<<"No"<<std::endl;
    else{
        auto p = DLL->findNode("fangsen");
        DLL->deleteNode(p);
        DLL->visitDLL();
    }
    DLL->insertNode(std::shared_ptr<Node>(new Node("46")));
    DLL->visitDLL();
    DLL->insertNode(std::shared_ptr<Node>(new Node("7831")));
    DLL->insertNode(std::shared_ptr<Node>(new Node("yilin")));
    DLL->visitDLL();
    if(DLL->findNode("7831") ==  nullptr) std::cout<<"No"<<std::endl;
    else{
        auto p = DLL->findNode("7831");
        DLL->deleteNode(p);
        DLL->visitDLL();
    }
    if(DLL->findNode("7831") ==  nullptr) std::cout<<"No"<<std::endl;
    else{
        auto p = DLL->findNode("7831");
        DLL->deleteNode(p);
        DLL->visitDLL();
    }
    return 0;
}