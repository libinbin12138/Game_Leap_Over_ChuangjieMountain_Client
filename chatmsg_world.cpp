#include "chatmsg_world.h"

ChatMsg_World::ChatMsg_World()
{

}

void ChatMsg_World::SetChatMsg(int id, QString _user, QString _content, int touxiangflag, QDate _date)
{
    chat_id=id;
    chat_user=_user;
    chat_content=_content;
    chat_date=_date;
    chat_touxiang=touxiangflag;
}

int ChatMsg_World::Get_chat_id()
{
    return chat_id;
}

QString ChatMsg_World::Get_chat_user()
{
    return chat_user;
}

QString ChatMsg_World::Get_chat_content()
{
    return chat_content;
}

QDate ChatMsg_World::Get_chat_date()
{
    return chat_date;
}

int ChatMsg_World::Get_chat_touxiang()
{
    return chat_touxiang;
}
