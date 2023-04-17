#ifndef PLAYER_H
#define PLAYER_H
#include<QString>

class Player
{
public:
    Player();
    void SetPlayer(QString _name,int _level,int gole_num,int dianquan,int TouxiangFlag);
    QString getName();
    int getLevel();
    int getGoldnum();
    int getDianquan();
    int getTouxiangflag();
private:
    QString name;
    int level;
    int Gold_num;
    int Dianquan;
    int TouxiangFlag;
};

#endif // PLAYER_H
