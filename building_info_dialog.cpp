#include "building_info_dialog.h"
#include "ui_building_info_dialog.h"
#include<QPainter>
#include<QFile>
#include<QString>
#include<QStringList>
#include<QDebug>

Building_Info_Dialog::Building_Info_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Building_Info_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("场景相关信息");
    this->setWindowIcon(QIcon(":/Building/Building (72).jpg"));
}

Building_Info_Dialog::~Building_Info_Dialog()
{
    delete ui;
}

void Building_Info_Dialog::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPixmap pix(":/Building/Building (72).jpg");
    paint.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Building_Info_Dialog::SetLineEditContent(int num)
{
    if(Building_info_list.size()==0)
    {
        qDebug()<<"Building_info_list为空";
        return;
    }
    int pos=0;
    for(auto single:Building_info_list)
    {
        if(pos==num)
        {
            switch(single->Get_BUilding_Flag())
            {
            case 1:
                ui->lineEdit->setText(single->Get_building_name());
                ui->lineEdit_6->setText(single->Get_User_name());
                break;
            case 2:


                break;
            default:

                break;
            }
        }
        pos++;
    }
}

void Building_Info_Dialog::SetLineEditContent_From_serve(int num, QString Username, int Grade)
{
    Read_Building_info();
    qDebug()<<"读取BildingInfo数据完成"<<num;
    if(num<0)
    {
        return;
    }
    int pos=0;
    if(Username.size()>0)
    {
        Building_Info *temp=new Building_Info;
        for(auto single:Building_info_list)
        {
            if(num==pos)
            {
                temp=single;
                temp->Set_User_nmae(Username);
                Building_info_list.replace(pos,temp);
                break;
            }
            pos++;
        }
    }
    //    if(Grade>0)
    //    {

    //    }

}

void Building_Info_Dialog::ClearLineEditContent()
{
    this->ui->lineEdit->clear();
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_4->clear();
    this->ui->lineEdit_5->clear();
    this->ui->lineEdit_6->clear();
    this->ui->lineEdit_7->clear();
    this->ui->lineEdit_8->clear();
    this->ui->lineEdit_9->clear();
    this->ui->lineEdit_10->clear();

    this->Building_info_list.clear();
}

void Building_Info_Dialog::Read_Building_info()
{
    QFile File("Building_Info.txt");
    if(!File.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开Building_Info.txt失败";
    };
    while (!File.atEnd())
    {
        if(File.atEnd())
        {
            break;
        }

        QString line=File.readLine();
        QStringList stringlist=line.split(" ");
        if(stringlist.size()<=0)
        {
            qDebug()<<"stringlist为空";
            return;
        }
        Building_Info *building_info=new Building_Info;

        building_info->Set_building_name(stringlist[0]);
        building_info->Set_User_nmae(stringlist[1]);
        building_info->Set_Building_Flag(stringlist[2].toInt());

        building_info->Set_Money(stringlist[3].toInt(),stringlist[4].toInt(),
                stringlist[5].toInt(),stringlist[6].toInt(),stringlist[7].toInt(),
                stringlist[8].toInt(),stringlist[9].toInt());

        qDebug()<<"初始化building_info成功";
        Building_info_list.append(building_info);
    }
    qDebug()<<"Building_info_list添加成功";
}
