#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
class CDog; //CDog must be declared firstly
class CMaster{
    CDog *dogs[10]; // cant use CDog dogs[10] !!
};

class CDog{
    CMaster m; //still wrong , many dogs have a same master
    // for example if one dog change the master, so, the dogs, which have
    // the same master must change one by one if using this "obj Method", cauz
    // we these dogs with same Master must be always "same"
    // Instead we should use pointer
};
*/
// Best way is like below
class CMaster;
class CDog{
    public:
    char* name_dog;
    CMaster *pm;
    CDog(char* s){
        name_dog = s;
    }
    ~CDog(){

    }
    void PrintMaster();
    void ChangeMaster(CMaster* _pm);
};

class CMaster{
    public:
        char* name_Master;
        CDog *dogs[10];
        int num;
        CMaster(char* s){
            for(int i=0;i<10;i++) dogs[i] = NULL;
            num = 0;
             name_Master = s;
        }
        ~CMaster(){

        }
        void set_Master(CDog* p_dog){
            (p_dog->pm) = this;
            dogs[num++] = p_dog;
        }
        void lost_dogs(CDog* p_dog){
            std::cout<<"lost "<<p_dog->name_dog<<" "<<p_dog<<std::endl;
            for(int i=0;i<10;i++){
                // std::cout<<dogs[i]<<" ";
                if(dogs[i] == p_dog){
                    std::cout<<"find! "<<dogs[i]->name_dog<<std::endl;
                    dogs[i] = NULL;
                    num--;
                    break;
                }
            }
        }
        void PrintDogs(){
            for(int i=0;i<10;i++){
                if(dogs[i] != NULL){
                    std::cout<<dogs[i]->name_dog<<" ";
                }
            }
            std::cout<<std::endl;
        }
};


void CDog::PrintMaster(){
    std::cout<<pm->name_Master<<std::endl;
}

void CDog::ChangeMaster(CMaster* pm_new){
         // std::cout<<"change Master "<<_pm<<std::endl;
        CMaster *tmp = pm;
        pm = pm_new;
        tmp->lost_dogs(this);
        pm_new->set_Master(this);

 }

int main(){
    char name_M1[] = "fangsen";
    char name_M2[] = "yilin";
    char name_D1[] = "huahua";
    char name_D2[] = "doudou";
    char name_D3[] = "erbao";
    char name_D4[] = "wangwang";
    CMaster* p_M1 = new CMaster(name_M1); 
    CMaster* p_M2 = new CMaster(name_M2);

    CDog* p_D1 = new CDog(name_D1);
    CDog* p_D2 = new CDog(name_D2);
    CDog* p_D3 = new CDog(name_D3);
    CDog* p_D4 = new CDog(name_D4);

    p_M1->set_Master(p_D1);
    p_M1->PrintDogs();
    p_M1->set_Master(p_D2);
    p_M1->PrintDogs();

    p_D1->PrintMaster();
    p_D2->PrintMaster();

    p_D1->ChangeMaster(p_M2);
    p_M2->PrintDogs();
    // std::cout<<"Maser "<<p_M2<<std::endl;
    p_D1->PrintMaster();
    p_M1->PrintDogs();

    std::cout<<"------------------"<<std::endl;
    p_M2->set_Master(p_D3);
    p_M2->PrintDogs();
    p_D3->PrintMaster();
    p_M2->set_Master(p_D4);
    p_M2->PrintDogs();
    p_D4->PrintMaster();
    std::cout<<"-----D4 change Master------"<<std::endl;
    p_D4->ChangeMaster(p_M1);
    p_D4->PrintMaster();
    p_M1->PrintDogs();
    p_M2->PrintDogs();
    return 0;
}