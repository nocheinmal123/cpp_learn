#include <string>
#include <string.h>
#include <iostream>

class TableTennisPlayer{
    private:
        std::string firstname;
        std::string lastname;
        bool hasTable;
    public:
        TableTennisPlayer(const std::string& fn = "none", const std::string& ln = "none", bool ht = false);
        void Name() const;
        bool HasTable() const;
        void ResetTable(bool v);
};

class RatedPlayer: public TableTennisPlayer{
    private:
        unsigned int rating; // add a data member
    public:
        RatedPlayer(unsigned int _rating = 0, const std::string& fn = "none", const std::string& ln = "none", bool ht = false);
        RatedPlayer(unsigned int _rating, const TableTennisPlayer&);
        unsigned int Rating() const;
        void ResetRating(unsigned int _rating);
};