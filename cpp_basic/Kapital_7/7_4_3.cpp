#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
// copy src.dat to dest.dat

int main(){
    std::ofstream oFile("src.dat", std::ios::out | std::ios::binary);
    int num = 3;
    while(num--){
        int x;
        std::cin>>x;
        oFile.write((char*)(&x),sizeof(int));
    }
    oFile.close();

    std::ofstream destFile("dest.dat", std::ios::out | std::ios::binary);
    std::ifstream srcFile("src.dat", std::ios::in | std::ios::binary);
    if(!destFile || !srcFile){
        std::cout<<"error"<<std::endl;
        return 0;
    }
    int x;
    while(srcFile.read((char*)(&x),sizeof(int))){
        std::cout<<"x = "<<x<<std::endl;
        destFile.write((char*)(&x),sizeof(int));
    }
    // char c;
    // while(srcFile.get(c)){
    //     destFile.put(c);
    // }
    srcFile.close();
    destFile.close();

    std::ifstream iFile("dest.dat", std::ios::in | std::ios::binary);
    while(iFile.read((char*)(&x), sizeof(int))){
        std::cout<<"read = "<<x<<std::endl;
    }
    iFile.close();
    std::cout<<typeid(iFile).name()<<std::endl;
    return 0;
}