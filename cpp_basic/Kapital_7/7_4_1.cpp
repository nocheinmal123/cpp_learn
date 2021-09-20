#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
// read/write file in binary way

struct Student{
    char name[20];
    int score;
};

int main(){
    std::ofstream fout("some.dat", std::ios::out | std::ios::binary);
    int x = 120;
    fout.write((const char*)(&x), sizeof(int)); //  need to change the type when using the write/read function
    fout.close();
    std::ifstream fin("some.dat", std::ios::in | std::ios::binary);
    int y;
    fin.read((char*)(&y),sizeof(int));
    fin.close();
    std::cout<<y<<std::endl;

    std::cout<<"------------------------"<<std::endl;

    Student s;
    int num = 2;
    std::ofstream oFile("students.dat", std::ios::out | std::ios::binary);
    while(num--){
        std::cin>>s.name>>s.score;
        oFile.write((char*)(&s),sizeof(s));
    }
    oFile.close();


    std::ifstream iFile("students.dat", std::ios::in | std::ios::binary);
    if(!iFile){
        std::cout<<"error"<<std::endl;
        return 0;
    }
    while(iFile.read((char*)(&s),sizeof(s))){
        int readedBytes = iFile.gcount(); // check how many bytes were been red
        std::cout<<readedBytes<<std::endl;
        std::cout<<s.name<<", "<<s.score<<std::endl;
    }    
    iFile.close();
    return 0;
}