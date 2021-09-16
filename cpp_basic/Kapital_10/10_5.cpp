#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
// for loop

class A{
    public:
        int n;
        A(int _n):n(_n){

        }
};


int main(){
    int arr[] = {1,2,3,4,5};
    for(int& e:arr) e *= 10;
    for(auto e:arr) std::cout<<e<<" "; std::cout<<std::endl;
    std::vector<A> st(arr,arr+5);
    for(auto& it:st) it.n *= 10;
    for(auto it:st) std::cout<<it.n<<" "; std::cout<<std::endl;
    return 0;
}