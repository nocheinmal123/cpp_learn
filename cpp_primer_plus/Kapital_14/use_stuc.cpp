#include "studentc.h"

const int quizzes = 2;

void set(Student& sa, int n){
    std::cout << "Enter the student's name please:\n";
    std::cin >> sa;
    std::cout << "Please enter " << n << " quiz sores:\n";
    for(int i=0;i<n;i++){
        std::cin >> sa[i];
    }
}



int main(){
    Student* ada[3] = {new Student(quizzes), new Student(quizzes), new Student(quizzes)};
    for(int i=0;i<3;i++) set(*ada[i], quizzes);
    for(int i=0;i<3;i++) std::cout << *ada[i] << std::endl;
    for(int i=0;i<3;i++) std::cout << ada[i]->Name() << std::endl;
    for(int i=0;i<3;i++) std::cout << ada[i]->Average() << std::endl;
    return 0;
}