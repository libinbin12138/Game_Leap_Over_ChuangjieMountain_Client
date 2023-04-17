
#ifndef MYPROTOBUFROOMREADYINFO_H
#define MYPROTOBUFROOMREADYINFO_H


#include "myprorobuf.h"
#include"dafuwen.pb.h"

using namespace dafuwenprotobuf;

struct MyprotobufRoomReadyInfoStruct
{
    int Room_ID;
    std::string Room_Name;
    std::string Room_Description;
    int Room_Maxnum;
    int Room_Flag=1;
    std::string Room_Pwd;
    std::string Room_AesKey;
    int Player_Order;
    std::string Player_Name;
    int Player_TouxiangFlag;
    int cfd;
    std::string IP;
    MyprotobufRoomReadyInfoStruct() // 构造函数来初始化各个成员变量的默认值
        : Room_ID(0), Room_Name(""), Room_Description(""), Room_Maxnum(4),
        Room_Flag(1), Room_Pwd(""), Room_AesKey(""), Player_Order(0),
        Player_Name(""), Player_TouxiangFlag(0), cfd(0), IP("") {}

};

class MyProtobufRoomReadyInfo: public MyProrobuf
{
public:
    MyProtobufRoomReadyInfo();
    virtual void initMessage(void * ptr);
    virtual std::string encodeMsg();
    virtual void* decodeMsg(std::string EnproStr) ;
private:
    std::string RoomReadyInfo_EnStr;
    Room_Info room_info;

};

#endif // MYPROTOBUFROOMREADYINFO_H
