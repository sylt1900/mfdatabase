#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#define DEBUG_OPT_FM 1

#include <string>
#include <fstream>
#include "Const.h"
#include <iostream>
#include "DBout.h"
#include "BlockAddr.h"
static bool isexist(std::string fn){
    bool ret=false;
    std::fstream f(fn,std::ios::in);
    if(f.is_open())
        ret=true;
    f.close();
    f.clear();
    return ret;
};
static bool rmfile(std::string fn){
    bool ret=false;
    if(remove(fn.c_str())==0)
        ret=true;
    return ret;
}
class Filemanager{
public:
    Filemanager(std::string fn);
    ~Filemanager();
    void write_data(unsigned char* data,int pos,int data_length);
    void get_data(int startpos,int endpos,unsigned char* data);
    void set_file_length(unsigned int length){this->filelength=length;}
    void close_file(){this->file_stream.close();}
    void open_file(std::string fn);
    BlockAddr get_a_block(int length);
    void write_(std::string str);
    void write_(int integer);
    void write_(bool boolean);
    //std::string read_();
    std::fstream file_stream;
    std::string filename;
    int filelength;
    int p_pos;
    int g_pos;
    private:
};

#endif // FILEMANAGER_H
