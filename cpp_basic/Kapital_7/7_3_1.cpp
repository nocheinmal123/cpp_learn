#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
// read and write of files
//                               ios
//                              /   \   
//                             /     \
//                      istream      ostream
//                       /  \         /    \
//                      /    \       /      \
//              ifstream      iostream      ofstream   
//            (can only read)     |       (can only write)
//                                v
//                              fstream 
//                          (read and write)
int main(){
    /*
    ios::in	    ifstream
                fstream	    打开文件用于读取数据。如果文件不存在，则打开出错。

    ios::out	ofstream
                fstream	打开文件用于写入数据。如果文件不存在，则新建该文件；如果文件原来就存在，则打开时清除原来的内容。

    ios::app	ofstream
                fstream	打开文件，用于在其尾部添加数据。如果文件不存在，则新建该文件。

    ios::ate	ifstream	打开一个已有的文件，并将文件读指针指向文件末尾。如果文件不存在，则打开出错。

    ios:: trunc	ofstream	打开文件时会清空内部存储的所有数据，单独使用时与 ios::out 相同。

    ios::binary	ifstream
                ofstream
                fstream	以二进制方式打开文件。若不指定此模式，则以文本模式打开。
    ios::in | ios::out	            fstream	    打开已存在的文件，既可读取其内容，也可向其写入数据。文件刚打开时，原有内容保持不变。如果文件不存在，则打开出错。
    ios::in | ios::out	            ofstream	打开已存在的文件，可以向其写入数据。文件刚打开时，原有内容保持不变。如果文件不存在，则打开出错。
    ios::in | ios::out | ios::trunc	fstream	    打开文件，既可读取其内容，也可向其写入数据。如果文件本来就存在，则打开时清除原来的内容；如果文件不存在，则新建该文件。
    */

    std::ofstream outFile("clients.dat", std::ios::out | std::ios::binary);
    // clients.dat  the name of the file, that's going to be created
    // ios::out     the way that the file willbe opened with
    //  -ios::out   into the file, and delete the original content of file
    //  -ios::app   into the file, and keep the original content, add at the tail of original content
    // is::binary   open this file in binary format

    // we can also define an obj of ofstream, then open with "open func"
    std::ofstream fout;
    fout.open("test.out", std::ios::binary);
    if(!fout){
        std::cout<<"File open error"<<std::endl;
    }
    // the path of file can be absolute path or relative path, but if no info about path
    // function will find it under right-now dir

    std::ofstream fout2("a.out",std::ios::app);
    long pos = fout.tellp(); // get the position of "write-pointer"
    pos = 10L;
    fout2.seekp(pos);                   //  move the "write-pointer" to the 10th char 
    fout2.seekp(pos, std::ios::beg);    //  count pos from begin
    fout2.seekp(pos, std::ios::cur);    //  count pos from current pos
    fout2.seekp(pos, std::ios::end);    //  count pos fromt tail

    std::ifstream fin("in.txt", std::ios::ate);
    long location = fin.tellg(); // get the position of "read-pointer"
    location = 10L;
    fin.seekg(location);                 //  move the "read-pointer" to the 10th char
    fin.seekg(location, std::ios::beg);  // count pos from begin
    fin.seekg(location, std::ios::cur);  // count pos from current pos
    fin.seekg(location, std::ios::end);  // count pos from end 
    return 0;
}