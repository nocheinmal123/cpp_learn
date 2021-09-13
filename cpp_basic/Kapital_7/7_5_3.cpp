#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>

template <class T, class Pred>
void Map(T s, T e, T x, Pred op){
    T i = &(*s);
    std::cout<<(*s)<<std::endl;
    std::cout<<(*i)<<std::endl;
    for(i=s;i<e;i++) *(x++) = op(*i);
}

int Cube(int x){ 
    std::cout<<x<<std::endl;
    return x*x*x;
}

int Square(int x){ return x*x;}


int main(){
    int a[5] = {1,2,3,4,5}; int b[5];
    Map(a,a+5,b,Cube);
    for(int i=0;i<5;i++) printf("%d ",b[i]); printf("\n");
    int c[5] = {3,4,5,6,7}; int d[5];
    Map(c,c+5,d,Square);
    for(int i=0;i<5;i++) printf("%d ",d[i]); printf("\n");
    return 0;
}