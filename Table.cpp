#include "Table.h"

Table::Table()
{
    //ctor
}

Table::Table(std::string tname)
{
    std::fstream f_open(tname+".table",std::ios::in);
    f_open >> this->tablename;
    f_open >> this->attr_length;
    for(int i=0;i<this->attr_length;i++){
        f_open >> this->attrs[i].attrname;
        f_open >> this->attrs[i].attrtype;
        f_open >> this->attrs[i].attrlength;
        f_open >> this->attrs[i].isnull;
        f_open >> this->attrs[i].ispkey;
        f_open >> this->attrs[i].isunique;
        if(this->attrs[i].ispkey){
            this->primary_key_pos=i;
        }
    }
    f_open.close();
    f_open.clear();
}


Table::Table(Table& t)
{
    this->tablename=t.tablename;
    this->attr_length=t.attr_length;
    this->tuber_length=t.tuber_length;
    this->tubers.assign(t.tubers.begin(),t.tubers.end());
    for(int i=0;i<t.attr_length;i++){
        this->attrs[i]=t.attrs[i];
    }
    this->primary_key_pos=t.primary_key_pos;
}

Table::~Table()
{
    //dtor
}
void Table::set_table(std::string tablename, int attr_length, int tuber_length, std::vector<Tuber>tubers, Attr attrs[32])
{
    this->tablename=tablename;
    this->attr_length=attr_length;
    this->tuber_length=tuber_length;
    this->tubers.assign(tubers.begin(),tubers.end());
    for(int i=0;i<attr_length;i++){
        this->attrs[i]=attrs[i];
    }

}


void Table::show_table()
{
    PrintScreen("[TABLE : "+this->tablename+"]\n");
    PrintScreen("[SIZE : "+std::to_string(this->attr_length)+"]\n");
    for(int i=0;i<this->attr_length;i++){
        this->attrs[i].show_attr();
    }
}
