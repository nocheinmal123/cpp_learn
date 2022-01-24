#include <iostream>
#include <string>
#include <string.h>

class DMA{
    public:
        DMA(){}
        virtual ~DMA(){}
        virtual void View() const = 0;
};


class baseDMA: public DMA{
    private:
        char* _label;
        int _rating;
    public:
        baseDMA(const char* label = "null", int rating = 0);
        baseDMA(const baseDMA&);
        virtual ~baseDMA();
        baseDMA& operator=(const baseDMA&);
        virtual void View() const;
        friend std::ostream& operator<<(std::ostream&, const baseDMA&);
};

baseDMA::baseDMA(const char* label, int rating):DMA(){
    _label = new char[strlen(label) + 1];
    strcpy(_label, label);
    _rating = rating;
}

baseDMA::baseDMA(const baseDMA& src){
    _label = new char[strlen(src._label) + 1];
    strcpy(_label, src._label);
    _rating = src._rating;
}

baseDMA::~baseDMA(){
    delete[] _label;   
}

baseDMA& baseDMA::operator=(const baseDMA& src){
    if(this == &src) return *this;
    delete[] _label;
    _label = new char[strlen(src._label) + 1];
    strcpy(_label, src._label);
    _rating = src._rating;
}

void baseDMA::View() const{
    std::cout << "in obj" << std::endl;
    std::cout  << "label: " << _label << ", " << "rating: " << _rating << std::endl;
}

std::ostream& operator<<(std::ostream& out, const baseDMA& src){
    using std::endl;
    out << "label: " << src._label << endl;
    out << "rating: " << src._rating << endl;
    return out;
}

class lacksDMA: public DMA{
    private:
        char* _color;
        char* _label;
        int _rating;
    public:
        lacksDMA(const char* color = "black", const char* _label = "null", int r = 0);
        lacksDMA(const lacksDMA&);
        lacksDMA& operator=(const lacksDMA&);
        ~lacksDMA();
        virtual void View() const;
        friend std::ostream& operator<<(std::ostream&, const lacksDMA&);
};

lacksDMA::lacksDMA(const char* color, const char* label, int r):DMA(){
    _color = new char[strlen(color) + 1];
    strcpy(_color, color);
    _label = new char[strlen(label) + 1];
    strcpy(_label, label);
    _rating = r;
}

lacksDMA::lacksDMA(const lacksDMA& src){
    _color = new char[strlen(src._color) + 1];
    strcpy(_color, src._color);
    _label = new char[strlen(src._label) + 1];
    strcpy(_label, src._label);
    _rating = src._rating;
}

lacksDMA::~lacksDMA(){

}

void lacksDMA::View() const{
    std::cout << "in obj" << std::endl;
    std::cout << "color: " << _color << ", ";
    std::cout  << "label: " << _label << ", " << "rating: " << _rating << std::endl;
}

std::ostream& operator<<(std::ostream& out, const lacksDMA& src){
    using std::endl;
    out << "color: " << src._color << endl;
    out << "label: " << src._label << endl;
    out << "rating: " << src._rating << endl;
    return out;
}