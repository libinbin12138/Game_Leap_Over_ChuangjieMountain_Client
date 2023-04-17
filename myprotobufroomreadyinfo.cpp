
#include "myprotobufroomreadyinfo.h"

MyProtobufRoomReadyInfo::MyProtobufRoomReadyInfo()
{

}

void MyProtobufRoomReadyInfo::initMessage(void *ptr)
{
    MyprotobufRoomReadyInfoStruct * RoomReadyInfoStruct=(MyprotobufRoomReadyInfoStruct*)ptr;
    room_info.set_room_id(RoomReadyInfoStruct->Room_ID);
    room_info.set_room_name(RoomReadyInfoStruct->Room_Name);
    room_info.set_room_description(RoomReadyInfoStruct->Room_Description);
    room_info.set_room_maxnum(RoomReadyInfoStruct->Room_Maxnum);
    room_info.set_room_flag(RoomReadyInfoStruct->Room_Flag);
    room_info.set_room_pwd(RoomReadyInfoStruct->Room_Pwd);
    room_info.set_room_aeskey(RoomReadyInfoStruct->Room_AesKey);
    room_info.set_player_order(RoomReadyInfoStruct->Player_Order);
    room_info.set_player_name(RoomReadyInfoStruct->Player_Name);
    room_info.set_player_touxiangflag(RoomReadyInfoStruct->Player_TouxiangFlag);
    room_info.set_cfd(RoomReadyInfoStruct->cfd);
    room_info.set_ip(RoomReadyInfoStruct->IP);

}

std::string MyProtobufRoomReadyInfo::encodeMsg()
{
    room_info.SerializeToString(&RoomReadyInfo_EnStr);
    return RoomReadyInfo_EnStr;
}

void *MyProtobufRoomReadyInfo::decodeMsg(std::string EnproStr)
{
    room_info.ParseFromString(EnproStr);
    return &room_info;
}

