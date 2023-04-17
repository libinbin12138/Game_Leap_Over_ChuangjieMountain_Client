#include "player.h"

Player::Player()
{

}

void Player::SetPlayer(QString _name, int _level, int gole_num, int dianquan, int TouxiangFlag)
{
    this->name=_name;
    this->level=_level;
    this->Gold_num=gole_num;
    this->Dianquan=dianquan;
    this->TouxiangFlag=TouxiangFlag;
}

QString Player::getName()
{
    return name;
}

int Player::getLevel()
{
    return level;
}

int Player::getGoldnum()
{
    return Gold_num;
}

int Player::getDianquan()
{
    return Dianquan;
}

int Player::getTouxiangflag()
{
    return TouxiangFlag;
}


