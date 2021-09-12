#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class CArray{
    private:
        int* p;
        int size;
        int cur;
    public:
        CArray(int _size = 0);
        ~CArray();
        void clear();
        void push_back(int v);
        int& operator[](const int index);
        CArray& operator=(const CArray& c);
        CArray(const CArray& c);
        void Print();
};


CArray::CArray(int _size):size(_size){
    if(size < 0){
        std::cout<<"negative size, can't initialize"<<std::endl;
    }
    if(size == 0) p = NULL;
    else p = new int[size];
    cur = 0;
}

CArray::~CArray(){
    if(p != NULL){
        delete []p;
        size = 0;
        cur = 0;
    }
}

// void CArray::clear(){
//    CArray::~CArray();
// }

int& CArray::operator[](const int index){
    if(index >= cur || index < 0){
        std::cout<<"can't visit this element"<<std::endl;
    }
    else{
        return *(p + index);
    }
}

CArray& CArray::operator=(const CArray& c){
    if(c.p == NULL){
        if(this->p != NULL) delete []p;
        this->p = NULL;
        this->size = 0;
        this->cur = 0;
    }
    else{
        if(this->p != NULL) this->p = NULL;
        this->p = new int[c.size];
        this->cur = c.cur;
     }
    memcpy(p,c.p,sizeof(int)*c.size);
    size = c.size;
    cur = c.cur;
    return *this;
}

CArray::CArray(const CArray& c){
    if(c.p == NULL){
        this->p = NULL;
        this->size = 0;
        this->cur = 0;
    }
    else{
        if(p != NULL) p = NULL;
        p = new int[c.size];
        cur = c.cur;
    }
    memcpy(p,c.p,sizeof(int)*c.size);
    size = c.size;
    cur = c.cur;
}

void CArray::push_back(int v){
    if(p != NULL){
        // int *temp_p = new int[size + 1];
        // memcpy(temp_p,p,sizeof(int)*size);
        // delete []p;
        // p = temp_p;
        if(cur == size){
            int *tem_p = new int [size*2];
            memcpy(tem_p,p,sizeof(int)*size);
            delete []p;
            p = tem_p;
            size  = (size << 1);
         }
    }
    else 
    {
        p = new int[1];
        size = 1;
        cur = 0;
    }
    p[cur ++] = v;
    std::cout<<"size = "<<size<<std::endl;
}

void CArray::Print(){
    for(int i=0;i<cur;i++) printf("%d ",*(p+i));
    printf("\n");
}

int main(){
    CArray a(10);
    for(int i=1;i<=8;i++) a.push_back(i);
    a.Print();
    a.push_back(100);
    a.Print();
    a.push_back(1000);
    a.Print();
    a.push_back(15);
    a.Print();
    a.push_back(16);
    a.Print();
    CArray b;
    std::cout<<"-------b-------"<<std::endl;
    b.Print();
    b.push_back(4);
    b.Print();
    b.push_back(5);
    b.Print();
    b.push_back(134);
    b.Print();
    CArray c(a);
    std::cout<<"--------c-------"<<std::endl;
    c.Print();
    c.push_back(1113);
    c.Print();
    a.Print();
    std::cout<<"--------d--------"<<std::endl;
    CArray d;
    d = b;
    d.Print();
    d.push_back(12);
    d.Print();
    d.push_back(190);
    d.Print();
    b.Print();
    d[2] = 100000;
    d.Print();
    b[0] = 90;
    b.Print();
    return 0;
}