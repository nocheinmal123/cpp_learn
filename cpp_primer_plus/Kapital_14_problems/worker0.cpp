#include "worker0.h"

Worker::Worker(const char* fullname, int id){
    _fullname = new char[strlen(fullname) + 1];
    strcpy(_fullname, fullname);
    _id = id;
}

Worker::Worker(const Worker& wk){
    _fullname = new char[strlen(wk._fullname) + 1];
    strcpy(_fullname, wk._fullname);
    _id = wk._id;
}

Worker::~Worker(){
    delete[] _fullname;
}

void Worker::Set(){
    std::cout << "Enter worker's name: ";
    std::cin >> _fullname;
    std::cout << "Enter worker's id: ";
    std::cin >> _id;
}

void Worker::Show() const{
    std::cout << "Name: " << _fullname << std::endl;
    std::cout << "Employer ID: " << _id << std::endl;
}

Waiter::Waiter(const char* fullname, int id, int panache):Worker(fullname, id){
    _panache = panache;
}

Waiter::Waiter(const Worker& wk, int panache):Worker(wk), _panache(panache){

}

void Waiter::Set(){
    Worker::Set();
    std::cout << "Enter waiter's panahe rating: ";
    std::cin >> _panache;
}

void Waiter::Show() const{
    std::cout << "Category: waiter\n";
    Worker::Show();
    std::cout << "Panache rating: " << _panache << std::endl;
}

Singer::Singer(const char* fullname, int id, int v):Worker(fullname, id), voice(v){

}

Singer::Singer(const Worker& wk, int v): Worker(wk), voice(v){

}

void Singer::Set(){
    Worker::Set();
    std::cout << "Enter the singer's vocal range: ";
    std::cin >> voice;
}

void Singer::Show() const{
    std::cout << "Category: singer\n";
    Worker::Show();
    std::cout << "Singer's vocal range: " << voice << std::endl;
}