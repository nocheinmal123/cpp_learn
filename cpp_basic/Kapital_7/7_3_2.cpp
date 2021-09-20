#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

int main(){
    std::vector<int> v;
    std::ifstream iFile("in.txt", std::ios::in);
    std::ofstream oFile("out.txt", std::ios::out);
    int x;
    while(iFile >> x){
        v.push_back(x);
    }
    std::sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++) oFile<<v[i]<<" "; //actually, th data will be wrote to the ROM, 
    // when the ROM is full, then data in ROM will be flushed into the hard-drive
    iFile.close();
    oFile.close();
    return 0;
}