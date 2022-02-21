#include "workerrmi.h"

Worker::Worker():fullname_("no one"), id_(0){

}

Worker::Worker(const std::string& fullname, int id):fullname_(fullname), id_(id){

}

Worker::Worker(const Worker& wk){
    fullname_ = wk.fullname_;
    id_ = wk.id_;
}

void Worker::Data() const{
    std::cout << "Name: " << fullname_ << std::endl;
    std::cout << "Employee ID:" << id_ << std::endl;
}

void Worker::Get(){
    std::cout <<"Enter the employee's name: ";
    std::cin >> fullname_;
    std::cout << "Enter the employee's ID: ";
    std::cin >> id_;
}


Waiter::Waiter(): Worker(), panache_(0){

}

Waiter::Waiter(const std::string& fullname, int id, int panache): Worker(fullname, id), panache_(panache){

}

Waiter::Waiter(const Worker& wk, int panache): Worker(wk), panache_(panache){

}

void Waiter::Data() const{
    std::cout << "panache rating: " << panache_ << std::endl;    
}

void Waiter::Get(){
    std::cout << "Enter waiter's panache rating: ";
    std::cin >> panache_;
}

void Waiter::Set(){
    Worker::Get();
    Get();
}

void Waiter::Show() const{
    Worker::Data();
    Data();
}

Singer::Singer(): Worker(), voice_(0){

}

Singer::Singer(const std::string& fullname, int id, int voice): Worker(fullname, id), voice_(voice){

}

Singer::Singer(const Worker& wk, int voice): Worker(wk), voice_(voice){

}

void Singer::Data() const{
    std::cout << "voice: " << voice_ << std::endl;
}

void Singer::Get(){
    std::cout << "Eneter singer's voice: ";
    std::cin >> voice_;
}

void Singer::Set(){
    Worker::Get();
    Get();
}

void Singer::Show() const{
    Worker::Data();
    Data();
}

Singingwaiter::Singingwaiter(){

}

Singingwaiter::Singingwaiter(const std::string& fullname, int id, int panache, int voice):Worker(fullname, id), Waiter(fullname, id, panache), Singer(fullname, id, voice){

}

Singingwaiter::Singingwaiter(const Worker& wk, int panache, int voice): Worker(wk), Waiter(wk, panache), Singer(wk, voice){

}

Singingwaiter::Singingwaiter(const Waiter& wt, int voice): Worker(wt), Waiter(wt), Singer(wt, voice){

}

Singingwaiter::Singingwaiter(const Singer& st, int panache): Worker(st), Waiter(st, panache), Singer(st){

}

void Singingwaiter::Data() const{
    Singer::Data();
    Waiter::Data();
}

void Singingwaiter::Get(){
    Singer::Get();
    Waiter::Get();
}

void Singingwaiter::Set(){
    Worker::Get();
    Get();
}

void Singingwaiter::Show() const{
    Worker::Data();
    Data();
}