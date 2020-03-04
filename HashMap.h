#ifndef HASHMAP_H
#define HASHMAP_H
#define MAX_GRID_SIZE 1048576
#include <list>
#include <vector>
#include "BlockAddr.h"
/*
前缀搜索树
select * from tablename where attr1="aaa*";
常数时间查找
select * from tablename where attr2=number;
*/


class Key_Value{
public:
    Key_Value(){};
    Key_Value(BlockAddr addr,int num){
        this->addr=addr;
        this->num=num;
    }
    Key_Value(const Key_Value& kv){
        this->addr=kv.addr;
        this->num=kv.num;
    }
    Key_Value& operator = (const Key_Value& kv){
        this->addr=kv.addr;
        this->num=kv.num;
        return *this;
    }
    BlockAddr addr;
    int num;
};

class HashMap
{
public:
    HashMap();
    std::list<Key_Value> p_grid[MAX_READ_LOCKS];
    int count_pos(int num){return num%MAX_READ_LOCKS;}
    int store(Key_Value kv){p_grid[count_pos(kv.num)].push_back(kv);}
    std::vector<Key_Value> getdata(int num){
        //Key_Value ret(BlockAddr(-1,-1),num);
        std::vector<Key_Value> kvs;
        int pos=count_pos(num);
        std::list<Key_Value>::iterator pos_;
        for(pos_=p_grid[pos].begin();pos_!=p_grid[pos].end();++pos_){
            if((*pos_).num==num){
                //ret.addr=*pos_;
                kvs.push_back(*pos_);
            }
        }
        return kvs;
    }
    void store_2_file(){
    //pos data data
    }

    ~HashMap();
private:
};

#endif // HASHMAP_H
