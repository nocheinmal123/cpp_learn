#include <iostream>

// base class using dma
class baseDMA{
    private:
        char* _label;
        int _rating;
    public:
        explicit baseDMA(const char* label = "null", int r = 0);
        baseDMA(const baseDMA&);
        baseDMA& operator=(const baseDMA&);
        friend std::ostream& operator<<(std::ostream& out, const baseDMA&);
        virtual ~baseDMA();
};

// derived class without DMA
// no destructor needed, cauz no dma-data in the part of lacksdma
// uses implicit copy con
// used implicit assignment operator
class lacksDMA: public baseDMA{
    private:
        enum class col{
            COL_LEN = 40
        };
        char _color[int(col::COL_LEN)];
    public: 
        explicit lacksDMA(const char* color = "blank", const char* label = "null", int r = 0);
        lacksDMA(const char * color, const baseDMA&);
        friend std::ostream& operator<<(std::ostream& out, const lacksDMA&);
};

// derived class with DMA-data
class hasDMA: public baseDMA{
    private:
        char* _style;
    public:
        explicit hasDMA(const char* style = "none", const char* label = "null", int r = 0);
        hasDMA(const char* style, const baseDMA&);
        hasDMA(const hasDMA&);
        hasDMA& operator=(const hasDMA&);
        friend std::ostream& operator<<(std::ostream& out, const hasDMA&);
        ~hasDMA();
};