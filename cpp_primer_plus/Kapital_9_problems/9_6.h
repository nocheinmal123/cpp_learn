#include <string>
#include <string.h>
namespace Golf{
    class golf{
        private:
            char* fullname;
            int handicap;
        public:
            golf(char* _fullname, int _handicap){
                int len = strlen(_fullname);
                fullname = new char[len + 1];
                memcpy(fullname, _fullname, (len+1)*sizeof(char));
                handicap = _handicap;
            }
            ~golf(){
                delete[] fullname;
            }
            void setgolf(const char* name, const int hc);
            void setgolf();
            void sethandicap(int hc);
            void showgolf() const;
    };
}