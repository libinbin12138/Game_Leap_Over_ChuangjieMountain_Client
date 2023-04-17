#ifndef CHATMSG_WORLD_H
#define CHATMSG_WORLD_H
#include<QString>
#include<QDate>

class ChatMsg_World
{
public:
    ChatMsg_World();
    void SetChatMsg(int id, QString _user, QString _content, int touxiangflag,QDate _date);
    int Get_chat_id();
    QString Get_chat_user();
    QString Get_chat_content();
    QDate Get_chat_date();
    int Get_chat_touxiang();
private:
    int chat_id;
    QString chat_user;
    QString chat_content;
    QDate chat_date;
    int chat_touxiang;
};

#endif // CHATMSG_WORLD_H
