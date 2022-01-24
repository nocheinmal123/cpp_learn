#include <iostream>
#include <string>
#include <string.h>

class Cd{
    private:
        char* _performer;
        char* _label;
        int _selections; 
        double _playtime;
    public:
        Cd(const char* performer = "default", const char* label = "default", int selection = 0, double playtime = 0);
        Cd(const Cd&);
        virtual ~Cd();
        virtual void Report() const;
        virtual Cd& operator=(const Cd&);
};

Cd::Cd(const char* performer, const char* label, int selection, double playtime){
   _performer = new char[strlen(performer) + 1];
   strcpy(_performer, performer); 
   _label = new char[strlen(label) + 1];
   strcpy(_label, label);
   _selections = selection;
   _playtime = playtime;
}

Cd::Cd(const Cd& src){
     _performer = new char[strlen(src._performer) + 1];
    strcpy(_performer, src._performer); 
    _label = new char[strlen(src._label) + 1];
    strcpy(_label, src._label);
    _selections = src._selections;
    _playtime = src._playtime;
}

Cd::~Cd(){
    delete[] _performer;
    delete[] _label;
}

void Cd::Report() const{
    std::cout << "Performer: " << _performer << std::endl;
    std::cout << "Label: " << _label << std::endl;
    std::cout << "Selections: " << _selections << std::endl;
    std::cout << "Playtime: " << _playtime << std::endl;
}

Cd& Cd::operator=(const Cd& src){
    if(this == &src) return *this;
    delete[] _performer;
    delete[] _label;
    _performer = new char[strlen(src._performer) + 1];
    strcpy(_performer, src._performer); 
    _label = new char[strlen(src._label) + 1];
    strcpy(_label, src._label);
    _selections = src._selections;
    _playtime = src._playtime;
}

class Classic: public Cd{
    private:
        char* _description;
   public:
        Classic(const char* description = "default", const char* performer = "default", const char* label = "default", int selection = 0, double playtime = 0);
        Classic(const char* description, const Cd&);
        Classic(const Classic&); 
        virtual ~Classic();
        virtual void Report() const override;
        virtual Classic& operator=(const Classic&) ;
};

Classic::Classic(const char* description, const char* performer, const char* label, int selection, double playtime):Cd(performer, label, selection, playtime){
    _description = new char[strlen(description) + 1];
    strcpy(_description, description);
}

Classic::Classic(const char* description, const Cd& src):Cd(src){
    _description = new char[strlen(description) + 1];
    strcpy(_description, description);
 }

Classic::Classic(const Classic& src):Cd(src){
     _description = new char[strlen(src._description) + 1];
     strcpy(_description, src._description);
}

Classic::~Classic(){
    delete[] _description;
}

void Classic::Report() const{
    Cd::Report();
    std::cout << "Description: " << std::endl;
}

Classic& Classic::operator=(const Classic& src){
    if(this == &src) return *this;
    Cd::operator=(src);
    delete[] _description;
    _description = new char[strlen(src._description) + 1];
    strcpy(_description, src._description);
    return *this;
}