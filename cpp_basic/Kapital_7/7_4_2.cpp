#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Student{
    char name[20];
    int score;
};

int main(){
    Student s;
    std::fstream iofile("students.dat", std::ios::in | std::ios::out | std::ios::binary);
    if(!iofile){
        std::cout<<"error"<<std::endl;
        return 0;
    }
    iofile.seekp(1*sizeof(s), std::ios::beg); // move "write-pointer" 1 student byte from the begin of file
    int num = 1;
    while(num--){
        std::cin>>s.name>>s.score;
        iofile.write((char*)(&s),sizeof(s));
    }
    iofile.close();
    std::ifstream iFile("students.dat", std::ios::in | std::ios::binary);
    if(!iFile){
        std::cout<<"read error"<<std::endl;
        return 0;
    }
    while(iFile.read((char*)(&s),sizeof(s))){
        std::cout<<s.name<<", "<<s.score<<std::endl;
    }
    return 0;
}