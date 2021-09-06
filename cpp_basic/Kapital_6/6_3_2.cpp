#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
class A{
    public:
        int a,b;
        A(int _a,int _b):a(_a),b(_b){

        }
        bool operator<(const A& c){ // when using operator overloading, use ref &, dont use * pointer 
            return this->a < (c).a;
        }
        void Print(){
            std::cout<<a<<", "<<b<<std::endl;
        }
};

void func1(int* q){
    int a = 22;
    q = &a;
    printf("in func *q = %d\n",*q);
}

void func2(int* q){
    int a = 22;
    *q = a;
    printf("in func *q = %d\n",*q);
}

int main(){
    A* p[10];
    p[0] = new A(1,3);
    p[1] = new A(0,4);
    p[2] = new A(8,2);
    for(int i=0;i<3;i++) p[i]->Print();
    if((*p[0])<(*p[1])) printf("yes\n");
    else printf("no\n");
    int a = 7;
    int* q = &a;
    func1(q);
    printf("%d\n",*q);
    func2(q);
    printf("%d\n",*q);
    return 0;
}