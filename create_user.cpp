#include "create_user.h"
#include "ui_create_user.h"
#include<QPainter>
#include<QMessageBox>
#include<QDebug>
#include<QTimer>
#include <QTcpSocket>
#include<QtNetwork>

#include<QCryptographicHash>

#include"log_in.h"

Create_User::Create_User(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Create_User)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    client=new QTcpSocket(this);

    connect(&timer_ReadFromServe, &QTimer::timeout,[=]()
    {
        RecvFrom_Serve();
    });

    connect(&timer_ParseMsg, &QTimer::timeout,[=]()
    {
        ParseMegFromServe();
        timer_ParseMsg.stop();
    });
    connect(ui->UserName, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
    connect(ui->PassWord, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
    connect(ui->VerifyPwd, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
}
Create_User::~Create_User()
{
    delete ui;
}

void Create_User::ParseMegFromServe()
{
    qDebug()<<"接受到Recv_data，=="<<Recv_data;
    if(Recv_data=="ok")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("注册成功，即将自动返回"));
        QTimer::singleShot(1500,m_box,SLOT(accept()));
        m_box->exec();

        ui->pushButton->setEnabled(true);
        timer_ReadFromServe.stop();
        Recv_data.clear();
        client->readAll().clear();
        delete client;
        client=NULL;
        this->close();
        return;
    }
    else if(Recv_data=="chongfu")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("游戏名重复，请重试"));
        QTimer::singleShot(1000,m_box,SLOT(accept()));
        m_box->exec();

        this->ui->pushButton->setEnabled(true);
        Recv_data.clear();
        client->readAll().clear();
        return;
    }
    else
    {
        QMessageBox::warning(this,"警告","注册失败,要获取更多信息请联系开发人员"
                                       "qq：1771132432");

        ui->pushButton->setEnabled(true);
        Recv_data.clear();
        client->readAll().clear();
        qDebug()<<"注册失败，请重试";
        return;
    }
}

void Create_User::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    if(ui->UserName->text().size()<=0||ui->PassWord->text().size()<=0||ui->VerifyPwd->text().size()<=0)
    {
        QMessageBox::warning(this,"警告","用户账号或密码为空");
        ui->pushButton->setEnabled(true);
        return;
    }

    if(ui->UserName->text().indexOf('@',0, Qt::CaseInsensitive)==-1)
    {
        qDebug()<<"ui->UserName->text().size()=="<<ui->UserName->text().size();
        if(ui->UserName->text().size()!=11)
        {
            qDebug()<<"判断1";
            QMessageBox::warning(this,"警告","请输入正确的手机号");
            ui->pushButton->setEnabled(true);
            return;
        }
        for(auto single:ui->UserName->text())
        {
            if(single>'9'||single.toLatin1()<'0')
            {
                qDebug()<<"判断2";
                qDebug()<<single;
                QMessageBox::warning(this,"警告","请输入正确的手机号");
                ui->pushButton->setEnabled(true);
                return;
            }
        }
    }
    if(ui->PassWord->text()!=ui->VerifyPwd->text())
    {
        QMessageBox::warning(this,"警告","两次输入的密码不一致，请确认?");
        ui->pushButton->setEnabled(true);
        return;
    }
    QString UserName;
    QString PassWord;
    QString Flag_num=QString("%1").arg(201);
    UserName=ui->UserName->text();
    PassWord=ui->PassWord->text();
    qDebug()<<"UserName=="<<UserName;

    /*换算密码hash值*/
    QCryptographicHash hash_creator(QCryptographicHash::Sha256);
    /*设置源数据，生成hash数据*/
    hash_creator.addData(PassWord.toUtf8());
    PassWord = QString(hash_creator.result().toHex()); //szPassword变成密码hash值了

    QString SendData=(Flag_num+" "+UserName+" "+PassWord);
    qDebug()<<"SendData=="<<SendData;
    QByteArray sendbyteArray=SendData.toUtf8();
    char *ch=sendbyteArray.data();
    qDebug()<<"ch=="<<ch;

    QMessageBox box(QMessageBox::Warning, "温馨提示", "当前版本无法修改或找回密码，请您确认！");
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    box.setButtonText(QMessageBox::Ok, QString("确定注册"));
    box.setButtonText(QMessageBox::No, QString("我再想想"));
    box.setDefaultButton(QMessageBox::Ok);
    int ret=box.exec();

    switch(ret)
    {
    case QMessageBox::Ok:
    {
        //client->connectToHost(QHostAddress("106.52.85.61"), 8989);
        client->connectToHost(QHostAddress("106.52.85.61"), 8989);
        if (client->waitForConnected(1000))//判断连接成功
        {
            client->write(ch);
            timer_ReadFromServe.start(1);
        }
        else
        {
            QMessageBox::warning(this,"警告","连接服务器失败, 要获取更多信息请联系开发人员qq：1771132432");
            ui->pushButton->setEnabled(true);
            return;
        }
    }
        break;
    case QMessageBox::No:
        this->ui->pushButton->setEnabled(true);
        return;
    };
}



void Create_User::RecvFrom_Serve()
{
    Recv_data = client->readAll();
    if(Recv_data.size()>=2)
    {
        timer_ReadFromServe.stop();
        timer_ParseMsg.start();
    }

}
void Create_User::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPixmap pix(":/Building/Building (66).jpg");
    paint.drawPixmap(0,0,this->width(),this->height(),pix);

}

void Create_User::closeEvent(QCloseEvent *event)
{
    this->ui->UserName->clear();
    ui->PassWord->clear();
    ui->VerifyPwd->clear();
    this->ui->pushButton->setEnabled(true);
    delete client;
    client=NULL;


}
