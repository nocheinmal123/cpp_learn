#include "13_dma.h"
#include <string>
#include <string.h>

baseDMA::baseDMA(const char* label, int r){
    _label = new char[strlen(label) + 1];
    strcpy(_label, label);
    _rating = r;
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
    return *this;
}

std::ostream& operator<<(std::ostream& out, const baseDMA& src){
    out << "Label: " << src._label << std::endl;
    out << "Rating:" << src._rating << std::endl;
    return out;
}

lacksDMA::lacksDMA(const char* color, const char* label, int r):baseDMA(label, r){
    memcpy(_color, color, 39*sizeof(char));
    _color[39] = '\0';
}

lacksDMA::lacksDMA(const char* color, const baseDMA& src):baseDMA(src){
     memcpy(_color, color, 39*sizeof(char));
    _color[39] = '\0';
}

std::ostream& operator<<(std::ostream& out, const lacksDMA& src){
    out << (const baseDMA&) src;
    out << "Color: " << src._color << std::endl;
    return out;
}

hasDMA::hasDMA(const char* style, const char* label, int r):baseDMA(label, r){
    _style = new char[strlen(style) + 1];
    strcpy(_style, style);
}

hasDMA::hasDMA(const char* style, const baseDMA& src):baseDMA(src){
    _style = new char[strlen(style) + 1];
    strcpy(_style, style);
}

hasDMA::hasDMA(const hasDMA& src):baseDMA(src){
    _style = new char[strlen(src._style) + 1];
    strcpy(_style, src._style);
}

hasDMA::~hasDMA(){
    delete[] _style;
}

hasDMA& hasDMA::operator=(const hasDMA& src){
    if(this == &src) return *this;
    baseDMA::operator=(src);
    delete[] _style;
    _style = new char[strlen(src._style) + 1];
    strcpy(_style, src._style);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const hasDMA& src){
    out << (const baseDMA&) src; // 强制转换，这里的 <<就是基类的 <<了
    out << "Style: " << src._style << std::endl;
    return out;
}