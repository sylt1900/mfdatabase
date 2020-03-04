#ifndef BINARY_H
#define BINARY_H
#include <string>
typedef unsigned char byte;
const byte FLOAT_LENGTH = sizeof(float)/sizeof(char);
const byte INT_LENGTH = sizeof(int)/sizeof(char);
class Binary
{
    public:
        Binary();
        Binary(float data);
        Binary(int data);
        Binary(std::string data);
        void setBin(float data);
        void setBin(int data);
        void setBin(std::string data);
        virtual ~Binary();
    private:
        byte* BinStream;
        byte StreamType;
        byte StreamLength;
};

#endif // BINARY_H
