#include "log_in.h"
#include "ui_log_in.h"
#include"create_user.h"

#include<QPainter>
#include<QMessageBox>
#include<QCryptographicHash>
#include<QDebug>
#include<QtNetwork>
#include<windows.h>
#include<game_mainpage.h>

Log_In::Log_In(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Log_In)
{
    ui->setupUi(this);
    create_user=new Create_User;
    SetPage();
}

Log_In::~Log_In()
{
    delete ui;
}


void Log_In::SetPage()
{
    this->setFixedSize(800,600);

    LineEdit_Key=new QLineEdit(this);
    int x=this->pos().x()+100;
    int y=this->pos().y()+530;
    LineEdit_Key->setFixedSize(600,50);
    LineEdit_Key->move(x,y);
    LineEdit_Key->setAlignment( Qt::AlignHCenter);
    LineEdit_Key->setText("请联系管理员(qq:1771132432)获取内测码");


    connect(&timer_ReadFromServe, &QTimer::timeout,[=]()
    {
        RecvFrom_Serve();
    });

    connect(&timer_ParseMsg, &QTimer::timeout,[=]()
    {
        ParseMegFromServe();
        timer_ParseMsg.stop();
    });
    connect(&timer_gamemain, &QTimer::timeout,[=]()
    {
        qDebug()<<" game_mainpage->MsgParseStatus=="<< game_mainpage->MsgParseStatus;
        if( game_mainpage->MsgParseStatus)
        {
            ShowGameMain();
            timer_gamemain.stop();
        };
    });
    connect(ui->Username, SIGNAL(returnPressed()), ui->pushButton_login, SLOT(click()), Qt::UniqueConnection);
    connect(ui->Pwd, SIGNAL(returnPressed()), ui->pushButton_login, SLOT(click()), Qt::UniqueConnection);
}

void Log_In::RecvFrom_Serve()
{
    if (client->waitForConnected(1000))
    {
        Recv_data = client->readAll();
        if(Recv_data.size()>=2)
        {
            timer_ParseMsg.start();
        }
    }
}

void Log_In::ParseMegFromServe()
{
    qDebug()<<"接受到Recv_data，=="<<Recv_data;

    if(Recv_data=="log_in")
    {
        //从服务器拉取数据初始化
        Recv_data.clear();
        client->readAll().clear();
        game_mainpage= new Game_MainPage;
        game_mainpage->SetPageFromServe(ui->Username->text().toUtf8());
        timer_gamemain.start();
        return;
    }
    else if(Recv_data=="noUser")
    {
        QMessageBox::warning(this,"警告","当前输入玩家账号不存在");

        ui->pushButton_login->setEnabled(true);
        Recv_data.clear();
        client->readAll().clear();
        qDebug()<<"用户不存在，请重试";
        return;
    }
    else if(Recv_data=="UserAlreadyOnline")
    {
        QMessageBox::warning(this,"警告","当前输入账号玩家已在线，请勿重复登录");

        ui->pushButton_login->setEnabled(true);
        Recv_data.clear();
        client->readAll().clear();
        qDebug()<<"用户已经登录，请重试";
        return;
    }
    else if(Recv_data=="pwdWrong")
    {
        QMessageBox::warning(this,"警告","输入的密码错误");

        ui->pushButton_login->setEnabled(true);
        Recv_data.clear();
        client->readAll().clear();
        qDebug()<<"注册失败，请重试";
        return;
    }
    else
    {
        QMessageBox::warning(this,"警告","登录失败,请重试");

        ui->pushButton_login->setEnabled(true);
        Recv_data.clear();
        client->readAll().clear();
        return;
    }
}
void Log_In::on_pushButton_create_clicked()
{
    create_user->show();
}

void Log_In::on_pushButton_login_clicked()
{
    ui->pushButton_login->setEnabled(false);

    if(ui->Username->text().size()<=0)
    {
        QMessageBox::warning(this,"警告","输入的玩家账号为空");
        ui->pushButton_login->setEnabled(true);
        return;
    }
    if(ui->Pwd->text().size()<=0)
    {
        QMessageBox::warning(this,"警告","输入的玩家密码为空");
        ui->pushButton_login->setEnabled(true);
        return;
    }
    QString Username=ui->Username->text();
    QString PassWord=ui->Pwd->text();
    QString Flag_num=QString("%1").arg(206);
    qDebug()<<"UserName=="<<Username;

    /*换算密码hash值*/
    QCryptographicHash hash_creator(QCryptographicHash::Sha256);
    /*设置源数据，生成hash数据*/
    hash_creator.addData(PassWord.toUtf8());
    PassWord = QString(hash_creator.result().toHex()); //szPassword变成密码hash值了

    QString SendData=(Flag_num+" "+Username+" "+PassWord);
    qDebug()<<"SendData=="<<SendData;
    QByteArray sendbyteArray=SendData.toUtf8();
    char *ch=sendbyteArray.data();
    qDebug()<<"ch=="<<ch;
    client=new QTcpSocket(this);
    client->connectToHost(QHostAddress("106.52.85.61"), 8989);
    if (client->waitForConnected(1000))//判断连接成功
    {
        client->write(ch);
        timer_ReadFromServe.start(1);
    }
    else
    {
        QMessageBox::warning(this,"警告","连接服务器失败, 要获取更多信息请联系开发人员qq：1771132432");
        ui->pushButton_login->setEnabled(true);
        return;
    }

}

void Log_In::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPixmap pix(":/Building/Building (1).jpg");
    paint.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Log_In::closeEvent(QCloseEvent *event)
{
    timer_gamemain.stop();
    timer_ParseMsg.stop();
    timer_ReadFromServe.stop();
    //    delete client;
    //    client=NULL;
}

void Log_In::ShowGameMain()
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("登录成功"));
    QTimer::singleShot(1000,m_box,SLOT(accept()));
    m_box->exec();

    game_mainpage->show();

    timer_ReadFromServe.stop();
    Recv_data.clear();
    client->readAll().clear();
    delete client;
    client =NULL;
    this->hide();
}




