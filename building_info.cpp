#include "building_info.h"

Building_Info::Building_Info():Building_grade(0),Force_sale_money(0)
{

}

void Building_Info::Set_building_name(QString _name)
{
    Build_name=_name;
}

void Building_Info::Set_User_nmae(QString _name)
{
    User_name=_name;
}

void Building_Info::Set_Money(int _sale_money, int one_level_upgrade_money, int one_level_charge_money, int two_level_upgrade_money, int two_level_charge_money, int three_level_upgrade_money, int three_level_charge_money)
{
    Sale_money=_sale_money;
    One_level_upgrade_money=one_level_upgrade_money;
    One_level_charge_money=one_level_charge_money;

    Two_level_upgrade_money=two_level_upgrade_money;
    Two_level_charge_money=two_level_charge_money;

    Three_level_upgrade_money=three_level_upgrade_money;
    Three_level_charge_money=three_level_charge_money;

}

void Building_Info::Set_Grade(int _Grade)
{
    Building_grade=_Grade;
}

void Building_Info::Set_Force_money(int _force_sale_money)
{
    Force_sale_money=_force_sale_money;
}

void Building_Info::Set_Building_Flag(int flag)
{
    BUilding_Flag=flag;
}

QString Building_Info::Get_building_name()
{
    return Build_name;
}

QString Building_Info::Get_User_name()
{
    return User_name;
}

int Building_Info::Get_sale_money()
{
    return Sale_money;
}

int Building_Info::Get_Force_sale_money()
{
    return Force_sale_money;
}

int Building_Info::Get_Building_grade()
{
    return Building_grade;
}

int Building_Info::Get_BUilding_Flag()
{
    return BUilding_Flag;
}

int Building_Info::Get_One_level_upgrade_money()
{
    return One_level_upgrade_money;
}

int Building_Info::Get_One_level_charge_money()
{
    return One_level_charge_money;
}

int Building_Info::Get_Two_level_upgrade_money()
{
    return Two_level_upgrade_money;
}

int Building_Info::Get_Two_level_charge_money()
{
    return Two_level_charge_money;
}

int Building_Info::Get_Three_level_upgrade_money()
{
    return Three_level_upgrade_money;
}

int Building_Info::Get_Three_level_charge_money()
{
    return Three_level_charge_money;
}



