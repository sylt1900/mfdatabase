#include "Attr.h"

Attr::Attr()
{
    //ctor
}

Attr::Attr(std::string aname, int atype, int alength, int pk, int uq, int nl)
{
    this->attrname=aname;
    this->attrtype=atype;
    this->attrlength=alength;
    this->ispkey=pk;
    this->isunique=uq;
    this->isnull=nl;
}

Attr::~Attr()
{
    //dtor
}
void Attr::show_attr()
{
    std::string attrname0,attrlength0,isunique0,isnull0,attrtype0,ispkey0;
    std::stringstream all2s;
    all2s <<this->attrname<<" "<<this->attrlength<<" "<<this->attrtype<<" "<<this->isnull<<" "<<this->ispkey<<" "<<this->isunique;
    all2s >>attrname0>>attrlength0>>attrtype0>>isnull0>>ispkey0>>isunique0;
    PrintScreen("[attrname:"+attrname0+"]\n");
    PrintScreen("attrlength:"+attrlength0+"\n");
    PrintScreen("isunique:"+isunique0+"\n");
    PrintScreen("isnull:"+isnull0+"\n");
    PrintScreen("attrtype:"+attrtype0+"\n");
    PrintScreen("isprimarykey:"+ispkey0+"\n");
}
void Attr::setAttr(std::string aname, int atype, int alength, int pk, int uq, int nl)
{
    this->attrname=aname;
    this->attrtype=atype;
    this->attrlength=alength;
    this->ispkey=pk;
    this->isunique=uq;
    this->isnull=nl;
}
