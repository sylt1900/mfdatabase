#ifndef TABLE_H
#define TABLE_H
#include "Tuber.h"
#include "Attr.h"
#include <vector>
#include "Const.h"
#include "DBout.h"
#include <string>
#include <fstream>

class Table
{
public:
    Table();
    ~Table();
    Table(std::string tname);
    Table(Table& t);
    Table& operator = (const Table& t){
        this->tablename=t.tablename;
        this->attr_length=t.attr_length;
        this->tuber_length=t.tuber_length;
        this->tubers.assign(t.tubers.begin(),t.tubers.end());
        for(int i=0;i<t.attr_length;i++){
            this->attrs[i]=t.attrs[i];
        }
        this->primary_key_pos=t.primary_key_pos;
        return *this;
    };
    std::string tablename="";
    int tuber_length=0;
    int attr_length=0;
    int primary_key_pos=0;
    Attr attrs[MAX_ATTR];
    std::vector<Tuber> tubers;
    void show_table();
    void set_table(std::string tablename,int attr_length,int tuber_length,std::vector<Tuber> tubers,Attr attrs[MAX_ATTR]);
protected:

private:
};

#endif // TABLE_H
