#ifndef BUILDING_INFO_H
#define BUILDING_INFO_H
#include<QString>

class Building_Info
{
public:
    Building_Info();

    void Set_building_name(QString _name);
    void Set_User_nmae(QString _name);

    void Set_Grade(int _Grade);
    void Set_Building_Flag(int flag);

    void Set_Force_money(int _force_sale_money);
    void Set_Money(int _sale_money,int one_level_upgrade_money,
                   int one_level_charge_money,int two_level_upgrade_money,
                   int two_level_charge_money,int three_level_upgrade_money,
                   int three_level_charge_money);



    QString Get_building_name();
    QString Get_User_name();

    int Get_Building_grade();
    int Get_BUilding_Flag();

    int Get_sale_money();
    int Get_Force_sale_money();

    int Get_One_level_upgrade_money();
    int Get_One_level_charge_money();

    int Get_Two_level_upgrade_money();
    int Get_Two_level_charge_money();

    int Get_Three_level_upgrade_money();
    int Get_Three_level_charge_money();


private:

    QString Build_name;//建筑名
    QString User_name;//拥有者姓名

    int Building_grade;//建筑等级
    int BUilding_Flag;//建筑标志

    int Sale_money;//初始出售价格
    int Force_sale_money;//强买价格

    int One_level_upgrade_money;
    int One_level_charge_money;

    int Two_level_upgrade_money;
    int Two_level_charge_money;

    int Three_level_upgrade_money;
    int Three_level_charge_money;


};

#endif // BUILDING_INFO_H
