#ifndef RECODERMANAGER_H
#define RECODERMANAGER_H
#define DEBUG_RM 0
#include <string>
#include "Attr.h"
#include "Const.h"
#include "Filemanager.h"
#include "DBout.h"
#include "Tuber.h"
#include "Buffmanager.h"
//#include "GlobalVar.h"
extern Buffmanager bufferlist_rm;
class RecoderManager
{
public:
    RecoderManager();
    ~RecoderManager();
    void RMCREATETABLE(std::string tablename,int attrlength,Attr attrs[MAX_ATTR]);
    void RMCREATEDB(std::string tablename);
    void RMCREATEINDEX(std::string tablename);
    //void RMCREATEBACK(std::string tablename);
    void RMCREATELINK(std::string tablename);
    void RMCREATEFILE(std::string fn);
    BlockAddr RMstoredata(Tuber tuber,std::string tablename);
    Tuber RMreaddata(BlockAddr addr,std::string tablename,Attr attrs[MAX_ATTR],int attrlength);
private:
};

#endif // RECODERMANAGER_H
