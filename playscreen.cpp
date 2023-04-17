#include "playscreen.h"
#include "ui_playscreen.h"
#include"mainwindow.h"

#include<QString>
#include<QDebug>
#include <QtGlobal>
#include<QTime>
#include <QtNetwork>
#include<QLabel>
#include<QPainter>
#include<QObject>

#include<windows.h>
#include"building_info_dialog.h"

PlayScreen::PlayScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayScreen),
    Old_Width(1800),Old_height(1000),
    label_Num(0)
{
    ui->setupUi(this);
    this->move(200,200);
    this->setFixedSize(Old_Width,Old_height);

    roll_btn=new QPushButton(this);
    roll_btn2=new QPushButton(this);

    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Set_Roll();

    Building_Button_width=Old_Width/14;
    Building_Button_height=Old_height/9;
    Set_BUilding_Button();


    client = new QTcpSocket(this);
    connect(client,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));

    //  开启鼠标捕捉事件
    //centralWidget()->setMouseTracking(true);
    this->setMouseTracking(true);

    building_info_diag=new Building_Info_Dialog;
    building_info_diag->hide();
}

PlayScreen::~PlayScreen()
{
    delete ui;
}


void PlayScreen::Set_Roll_Pushbutton_Icon(PlayScreen::RollingStatus status)
{
    Roll_num1=rand()%12+1;
    Roll_num2=rand()%12+1;

    if(status==2)
    {
        if(Roll_num1%2==0)
        {
            Roll_num1--;
        }
        if(Roll_num2%2==0)
        {
            Roll_num2--;
        }
    }
    QString roll_icon_name1=QString(":/Roll/shaking%1.png").arg(Roll_num1);
    QString roll_icon_name2=QString(":/Roll/shaking%1.png").arg(Roll_num2);
    roll_btn->setIcon(QIcon(roll_icon_name1));
    roll_btn2->setIcon(QIcon(roll_icon_name2));
}

void PlayScreen::Set_Roll()
{
    roll_btn->resize(200,200);
    roll_btn->move(this->width()/2-roll_btn->width()-100,this->height()/2-roll_btn->height()-50);
    roll_btn->setStyleSheet("QPushButton{border:Opx}");
    roll_btn->setIconSize(QSize(200,200));

    roll_btn2->resize(200,200);
    roll_btn2->move(this->width()/2+100,this->height()/2-roll_btn2->height()-50);
    roll_btn2->setStyleSheet("QPushButton{border:Opx}");
    roll_btn2->setIconSize(QSize(200,200));
    //设置骰子开始的点数
    Set_Roll_Pushbutton_Icon(RollingStatus::Rollfinish);

    connect(&timer_Rollstart,&QTimer::timeout,[=]()
    {
        Set_Roll_Pushbutton_Icon(RollingStatus::Rolling);
    });

    connect(&timer_finish,&QTimer::timeout,[=]()
    {
        roll_btn->setEnabled(true);
        roll_btn2->setEnabled(true);
        timer_Rollstart.stop();
        timer_finish.stop();
        Set_Roll_Pushbutton_Icon(RollingStatus::Rollfinish);

        qDebug()<<"Roll_num1==="<<Roll_num1;
        qDebug()<<"Roll_num2==="<<Roll_num2;
        Roll_final_num=((Roll_num1+1)/2+(Roll_num2+1)/2);

    });

    connect(roll_btn,&QPushButton::clicked,[=]()
    {
        roll_btn->setEnabled(false);
        roll_btn2->setEnabled(false);
        timer_Rollstart.start(5);
        timer_finish.start(1000);
    });

    connect(roll_btn2,&QPushButton::clicked,[=]()
    {
        roll_btn->setEnabled(false);
        roll_btn2->setEnabled(false);
        timer_Rollstart.start(5);
        timer_finish.start(1000);
    });
}

void PlayScreen::Set_BUilding_Button()
{
    for(int i=0;i<14;i++)
    {
        QPushButton *btn=new QPushButton(this);
        btn->resize(this->Building_Button_width,this->Building_Button_height);
        btn->move(this->width()-Building_Button_width*(i+1),this->height()-Building_Button_height);
        btn->setStyleSheet("QPushButton{border:Opx}");
        btn->setStyleSheet(QString("border-image:url(:/Building/Building (%1).jpg);color:rgb(0,0,0);").arg(i+1));
        btn->setText(QString("按钮%1").arg(i+1));
        connect(btn,&QPushButton::clicked,[=]
        {
            qDebug()<<"点击了按钮"<<i+1;
            SendData(i);
        });
        btn->setMouseTracking(true);//开启鼠标移动事件
        Build_Button_list.append(btn);
    }
    int First_column=1;
    for(int i=14;i<21;i++)
    {
        First_column++;
        QPushButton *btn=new QPushButton(this);
        btn->resize(this->Building_Button_width,this->Building_Button_height);
        btn->move(0,this->height()-Building_Button_height*First_column);
        btn->setStyleSheet("QPushButton{border:Opx}");
        btn->setStyleSheet(QString("border-image:url(:/Building/Building (%1).jpg);color:rgb(0,0,0);").arg(i+1));
        btn->setText(QString("按钮%1").arg(i+1));
        connect(btn,&QPushButton::clicked,[=]
        {
            qDebug()<<"点击了按钮"<<i+1;
            SendData(i);
        });
        btn->setMouseTracking(true);
        Build_Button_list.append(btn);
    }
    int First_line=0;
    for(int i=21;i<35;i++)
    {
        QPushButton *btn=new QPushButton(this);
        btn->resize(this->Building_Button_width,this->Building_Button_height);
        btn->move(this->Building_Button_width*First_line,0);
        btn->setStyleSheet("QPushButton{border:Opx}");
        btn->setStyleSheet(QString("border-image:url(:/Building/Building (%1).jpg);color:rgb(0,0,0);").arg(i+1));
        btn->setText(QString("按钮%1").arg(i+1));
        connect(btn,&QPushButton::clicked,[=]
        {
            qDebug()<<"点击了按钮"<<i+1;
            SendData(i);
        });
        First_line++;
        btn->setMouseTracking(true);
        Build_Button_list.append(btn);
    }
    int Second_column=1;
    for(int i=35;i<42;i++)
    {
        QPushButton *btn=new QPushButton(this);
        btn->resize(this->Building_Button_width,this->Building_Button_height);
        btn->move(this->width()-this->Building_Button_width,this->Building_Button_height*Second_column);
        btn->setStyleSheet("QPushButton{border:Opx}");
        btn->setStyleSheet(QString("border-image:url(:/Building/Building (%1).jpg);color:rgb(0,0,0);").arg(i+1));
        btn->setText(QString("按钮%1").arg(i+1));
        connect(btn,&QPushButton::clicked,[=]
        {
            qDebug()<<"点击了按钮"<<i+1;
            SendData(i);
        });
        Second_column++;
        btn->setMouseTracking(true);
        Build_Button_list.append(btn);
    }
}

void PlayScreen::paintEvent(QPaintEvent *event)
{

    QPainter paint(this);
    paint.translate(this->Building_Button_width,this->Building_Button_height);
    QPixmap pix(":/Building/Building (71).jpg");
    paint.drawPixmap(0,0,this->width()-this->Building_Button_width,this->height()-this->Building_Button_height,pix);
}

void PlayScreen::mouseMoveEvent(QMouseEvent *event)
{
    // 判断鼠标是否在pushButton上

    Sleep(350);
    int num=0;

    for(auto single:Build_Button_list)
    {
        if (single->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            qDebug()<<"mouseevent num=="<<num;
            if((num+1)%5==0)
            {
                continue;
            }
            qDebug()<<"按钮"<<num+1;
            //QString("李某")
            qDebug()<<"开始从服务器接收数据";
            building_info_diag->SetLineEditContent_From_serve(2,QString("李某"),0);
            qDebug()<<"从服务器接收数据完成";

            building_info_diag->SetLineEditContent(num);
            qDebug()<<"设置lineedit信息完成"<<num;
            building_info_diag->move(single->geometry().x(),single->geometry().y());
            building_info_diag->show();
            return;
        }
        else
        {
            building_info_diag->ClearLineEditContent();
            building_info_diag->hide();
        }
        num++;
    }
}

void PlayScreen::SendData(int num)
{
    qDebug()<<"num==="<<num;
    char*  ch;
    QByteArray ba = QString("%1").arg(num).toLatin1(); // must
    ch=ba.data();

    qDebug()<<"ch==="<<ch;
    client->connectToHost(QHostAddress("192.168.31.117"), 8989);

    client->write(ch);
}
void PlayScreen::slot_recvmessage()
{
    //接收来自服务器的消息
    QByteArray byteArray = this->client->readAll();
    QString recvMessage =byteArray;// tr("recv from server: ") + byteArray + QDateTime::currentDateTime().toString(" yyyy-M-dd hh:mm:ss") + tr("\n");
    qDebug()<<recvMessage;

}
