#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class CArray{
    private:
        int size;
        int *ptr; // -----> dynamic distribution, neet a pointer
    public:
        CArray(int num = 0); // num means the num of element
        CArray(const CArray &x);
        ~CArray();
        void push_back(int v);
        int length() const;
        int & operator[](int index);
        CArray & operator=(const CArray &x);
};

CArray::CArray(int num):size(num){
   if(num == 0) ptr = NULL;
   else ptr = new int[num]; 
}

CArray::CArray(const CArray &x){
    if(x.ptr == NULL){
        ptr = NULL;
        size = 0;
        return;
    }
    ptr = new int[x.size];
    memcpy(ptr,x.ptr,sizeof(int) * x.size);
    size = x.size;
}

CArray::~CArray(){
    if(ptr) delete []ptr;
}

int & CArray::operator[](int index){
    return *(ptr + index);
}

CArray & CArray::operator=(const CArray &x){
    if(ptr == x.ptr) return *this;
    if(x.ptr == NULL){
        if(ptr) delete []ptr;
        ptr = NULL;
        size = 0;
        return *this;
    }
    if(size < x.size){
        if(ptr) delete []ptr;
        ptr = new int [x.size];
    }
    memcpy(ptr,x.ptr,sizeof(int)*x.size);
    size = x.size;
    return *this;
}

void CArray::push_back(int v){
   if(ptr){
       int *tmp_ptr = new int[size + 1];
       memcpy(tmp_ptr,ptr,sizeof(int)*size);
       delete []ptr;
       ptr = tmp_ptr;
   }
   else ptr = new int[1];
   ptr[size++] = v;
}

int CArray::length() const{
    return size;
}

int main(){
    CArray a;
    for(int i=0;i<5;i++){
        a.push_back(i); // ------> dynamic distribution
    }
    CArray a2,a3;
    a2 = a; // -----> need reload "="
    for(int i=0;i<a.length();i++) std::cout<<a2[i]<<" "; // ----> need reload "[]"
    a2 = a3;
    for(int i=0;i<a2.length();i++) std::cout<<a2[i]<<" ";
    std::cout<<std::endl;
    a[3] = 100;
    CArray a4(a); // ----> self-defined copy con
    for(int i=0;i<a4.length();i++) std::cout<<a4[i]<<" ";
    std::cout<<std::endl;
    return 0;
}