#ifndef ATTR_H
#define ATTR_H
#include <string>
#include <sstream>
#include "DBout.h"
class Attr
{
public:
    Attr();
    Attr(std::string aname,int atype,int alength,int pk,int uq,int nl);
    virtual ~Attr();
    std::string attrname="";
    int attrtype=-1;
    int attrlength=0;
    bool ispkey=false;
    bool isunique=false;
    bool isnull=false;
    void setAttr(std::string aname,int atype,int alength,int pk,int uq,int nl);
    void show_attr();
protected:

private:
};

#endif // ATTR_H
