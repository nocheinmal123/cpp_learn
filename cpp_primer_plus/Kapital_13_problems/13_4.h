#include <iostream>
#include <string>
#include <string.h>

class Port{
    private:
        char* brand;
        char* style;
        int bottles;
    public:
        Port(const char* br = "none", int b = 0, const char * st = "none");
        Port(const Port&);
        virtual ~Port();
        Port& operator=(const Port&);
        Port& operator+=(int b); //add b to bottles
        Port& operator-=(int b); // 
        int BottleCount() const;
        virtual void Show() const;
        friend std::ostream& operator<<(std::ostream& out, const Port&);
};

Port::Port(const char* br, int b, const char* st){
    brand = new char[strlen(br) + 1];
    strcpy(brand, br);
    style = new char[strlen(st) + 1];
    strcpy(style, st);
    bottles = b;
}

Port::Port(const Port& src){
    brand = new char[strlen(src.brand) + 1];
    strcpy(brand, src.brand);
    style = new char[strlen(src.style) + 1];
    strcpy(style, src.style);
    bottles = src.bottles;
}

Port::~Port(){
    delete[] brand;
    delete[] style;
}

Port& Port::operator=(const Port& src){
    if(this == &src) return *this;
    delete[] brand;
    delete[] style;
    brand = new char[strlen(src.brand) + 1];
    strcpy(brand, src.brand);
    style = new char[strlen(src.style) + 1];
    strcpy(style, src.style);
    bottles = src.bottles;
    return *this;
}

Port& Port::operator+=(int b){
    bottles += b;
    return *this;
}

Port& Port::operator-=(int b){
    bottles -= b;
    return *this;
}

int Port::BottleCount() const{
    return bottles;
}

void Port::Show() const{
    using std::cout;
    using std::endl;
    cout << "Brand: " << brand << endl;
    cout << "Kind: " << style << endl;
    cout << "Bottles: " << bottles << endl;
}

std::ostream& operator<<(std::ostream& out, const Port& p){
    out << p.brand << ", " << p.style << ", " << p.bottles;
    return out;
}

class VintagePort: public Port{
    private:
        char* nickname;
        int year;
    public:
        VintagePort();
        VintagePort(const char* br, int b, const char* nn, int y);
        VintagePort(const VintagePort&);
        ~VintagePort();
        VintagePort& operator=(const VintagePort&);
        virtual void Show() const override;
        friend std::ostream& operator<<(std::ostream&, const VintagePort&);
};

VintagePort::VintagePort(){
    
}

VintagePort::VintagePort(const char* br, int b, const char* nn , int y):Port(br, b){
    nickname = new char[strlen(nn) + 1];
    strcpy(nickname, nn);
    year = y;
}

VintagePort::VintagePort(const VintagePort& src):Port(src){
    nickname = new char[strlen(src.nickname) + 1];
    strcpy(nickname, src.nickname);
    year = src.year;
}

VintagePort::~VintagePort(){
    delete[] nickname;
}

VintagePort& VintagePort::operator=(const VintagePort& src){
    if(this == &src) return *this;
    Port::operator=(src);
    delete[] nickname;
    nickname = new char[strlen(src.nickname) + 1];
    strcpy(nickname, src.nickname);
    year = src.year;
    return *this;
}

void VintagePort::Show() const{
    Port::Show();
    std::cout << "nickname: " << nickname << std::endl;
    std::cout << "year: " << year << std::endl;
}

std::ostream& operator<<(std::ostream& out, const VintagePort& src){
    out << (const Port&)src;
    out << ", " << src.nickname << ", " << src.year;
    return out;
}
