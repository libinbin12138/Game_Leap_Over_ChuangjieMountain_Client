#include "game_ready_page.h"
#include "ui_game_ready_page.h"
#include<QPushButton>

#include<QDebug>
#include<QString>
#include <QtNetwork>
#include<QPainter>
#include<QMessageBox>
#include <iostream>
#include"MyRsa.h"

Game_Ready_Page::Game_Ready_Page(QWidget *parent) :
    QMainWindow(parent),
    ReadyPageStatus(false),
    ui(new Ui::Game_Ready_Page)
{
    ui->setupUi(this);

    Init_Page();

}

Game_Ready_Page::~Game_Ready_Page()
{
    delete ui;
}

void Game_Ready_Page::SetPage_FromServe(QString uname)
{
    if (client->waitForConnected(1000))//判断连接成功
    {

        QString chatmsg;
        chatmsg=QString::fromStdString(*SendDataSet(1,"设置页面"));
        qDebug()<<"聊天发送的chatmsg数据为"<<chatmsg;

        QByteArray sendbyteArray=chatmsg.toUtf8();
        qDebug()<<"聊天发送的sendbyteArray数据为"<<sendbyteArray.toBase64();
                                                                   client->write(sendbyteArray.toBase64());
    }
    else
    {
        QMessageBox::warning(this,"警告","连接服务器失败,正在重试");
        //        while(!client->waitForConnected(1000))
        //        {
        //            client=new QTcpSocket(this);
        //            client->connectToHost(QHostAddress("192.168.127.132"), 8989);
        //            if (client->waitForConnected(1000))//判断连接成功
        //            {
        //                QString Flag_num=QString("%1").arg(600);
        //                QString Send_data=Flag_num+" "+uname;
        //                QByteArray sendbyteArray=Send_data.toUtf8();
        //                char *ch=sendbyteArray.data();
        //                qDebug()<<"ch=="<<ch;
        //                client->write(ch);

        //                Send_data.clear();
        //                sendbyteArray.clear();
        //                //timer_recvfromServe.start(50);
        //                break;
        //            }
        //        }

    }
}

void Game_Ready_Page::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPixmap pix(":/Building/Building (52).jpg");
    paint.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Game_Ready_Page::Init_Page()
{
    this->setFixedSize(1400,900);
    client=new QTcpSocket(this);
    client->connectToHost(QHostAddress("192.168.127.132"), 8989);
    HideChatMsg();
}

void Game_Ready_Page::HideChatMsg()
{
    ui->lineEdit_Chatmsg1->hide();
    ui->lineEdit_Chatmsg2->hide();
    ui->lineEdit_Chatmsg3->hide();
    ui->lineEdit_Chatmsg4->hide();
    ui->lineEdit_Chatmsg5->hide();
    ui->lineEdit_Chatmsg6->hide();
    ui->lineEdit_ChatmsgMychat->hide();

    ui->lineEdit_Chatname1->hide();
    ui->lineEdit_Chatname2->hide();
    ui->lineEdit_Chatname3->hide();
    ui->lineEdit_Chatname4->hide();
    ui->lineEdit_Chatname5->hide();
    ui->lineEdit_Chatname6->hide();

    ui->pushButton_SendChatmsg->hide();
}

int Game_Ready_Page::SetChatMsg()
{
    MyRsa *myrsa=new MyRsa;
    myrsa->Create();
    myrsa->Write_Pri();
    myrsa->Write_Pub();
    // string endata=myrsa->Get_encrypt_Value("Base64测试成功");
    string pubkeystring=myrsa->Read_RPub_To_String();
    //string sendcontent=endata+" "+pubkeystring;
    qDebug()<<"公钥为"<<pubkeystring.data();
                                   QString chatmsg;

    chatmsg=QString::fromStdString(*SendDataSet(1,string("我他么就不信这插上步步安保法副编发发发法辑部覅币佛那份不币发个斜币发个斜了我草发")));
    QByteArray sendbyteArray=chatmsg.toUtf8();
    qDebug()<<"聊天发送的sendbyteArray数据为"<<sendbyteArray;
        qDebug()<<"聊天发送的sendbyteArray.toBase64数据为"<<sendbyteArray.toBase64();

                                                                            client->write(sendbyteArray.toBase64());
    return 0;
}

int Game_Ready_Page::RecvData()
{

    return 0;
}

std::string *Game_Ready_Page::SendDataSet(int flag,std::string content)
{
    unsigned int length = 0;
    int id = flag;
    std::string MsgContemnt;
    MsgContemnt=content;

    length =MsgContemnt.size();
    qDebug()<<"length=="<<length;

    auto pret = new std::string();


    pret->push_back((length >> 0) & 0xff);
    pret->push_back((length >> 8) & 0xff);
    pret->push_back((length >> 16) & 0xff);
    pret->push_back((length >> 24) & 0xff);

    pret->push_back((id >> 0) & 0xff);
    pret->push_back((id >> 8) & 0xff);
    pret->push_back((id >> 16) & 0xff);
    pret->push_back((id >> 24) & 0xff);

    pret->append(MsgContemnt);

    return pret;
}



void Game_Ready_Page::on_pushButton_ShowChatMsg_clicked()
{
    if(ui->pushButton_ShowChatMsg->text()=="显示消息")
    {
        ui->pushButton_SendChatmsg->show();
        ui->pushButton_ShowChatMsg->setText("隐藏消息");
    }
    else
    {
        ui->pushButton_ShowChatMsg->setText("显示消息");

    }
}


void Game_Ready_Page::on_pushButton_SendChatmsg_clicked()
{
    if (client->waitForConnected(1000))//判断连接成功
    {
        SetChatMsg();
    }
    else
    {
        QMessageBox::warning(this,"警告","连接服务器失败,正在重试");
    }

}

