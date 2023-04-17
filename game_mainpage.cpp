#include "game_mainpage.h"
#include "ui_game_mainpage.h"
#include<QPainter>
#include<QTcpSocket>
#include<QtNetwork>
#include<QMessageBox>
#include<QDebug>
#include<QStringList>
#include<QTextEdit>
#include <QPlainTextEdit>
#include<QFile>
#include<windows.h>
#include"player.h"
#include<QtCore5Compat/QTextCodec>
#include"chatmsg_world.h"
#include<QStandardItemModel>
#include"game_ready_page.h"
#include"MyRsa.h"
#include"myprorobuf.h"
#include"myprotobufrsakey.h"
#include"myprotobufroomreadyinfo.h"
#include<QCryptographicHash>
#include"MyAes.h"
static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}
std::string DecodeBase64( const std::string& encoded_string)
{
    size_t in_len = encoded_string.size();
    size_t i = 0;
    size_t j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    cout << "base64解码完成" << endl;
        return ret;
}
std::string plaintext_to_binary(const char* plaintext, int len)
{
        std::string result;
        for (int i = 0; i < len; ++i)
        {
        unsigned char c = plaintext[i];
        for (int j = 0; j < 8; ++j)
        {
            result += (c & 0x80) ? "1" : "0";
            c <<= 1;
        }
        }
        return result;
}
std::string binary_to_plaintext(const std::string& binary)
{
        std::string result;
        for (size_t i = 0; i < binary.size(); i += 8)
        {
        unsigned char c = 0;
        for (int j = 0; j < 8; ++j)
        {
            c <<= 1;
            c |= (binary[i + j] == '1') ? 0x01 : 0x00;
        }
        result += c;
        }
        return result;
}
void Test()
{
        const char* pt = "AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法。所谓对称密钥，就是说加密和解密用的是同一个密钥，消息的发送方和接收方在消息传递前需要享有这个密钥。和非对称密钥体系不同，这里的密钥是双方保密的，不会让任何第三方知道。";
        cout << "str.size()" <<strlen(pt)+1 << endl;
        MyAes* ma = new MyAes("1234567887654321");
        cout << "加密数据" << ma->Aes_Encode(pt) << endl;
                                  ma->Aes_Decode(ma->Aes_Encode(pt),strlen(pt)+1);
}

Game_MainPage::Game_MainPage(QWidget *parent) :
    QMainWindow(parent),MsgParseStatus(false),
    ui(new Ui::Game_MainPage),pos_ChatMsg_World(0),Room_id(-1)
{

    ui->setupUi(this);
    //Recv_data.resize(4096*3);

    client_init=new QTcpSocket(this);
    client_init->connectToHost(QHostAddress("106.52.85.61"), 8989);
    SetPage();
    ui->textEdit_StartRoom->hide();
    ui->pushButton_CreateRoom->hide();
    ui->pushButton_Join_Room->hide();
    ui->pushButton_JoinRandomRoom->hide();
    ui->pushButton_Room_back->hide();

    ui->label_CreateRoomName->hide();
    ui->label_CreateRoomFlag->hide();
    ui->label_CreateRoomPasswd->hide();
    ui->label_CreateRoomDescription->hide();
    ui->lineEdit_CreateRoom->hide();
    ui->lineEdit_CreateRoomPasswd->hide();
    ui->lineEdit_CreateRoomDescription->hide();

    ui->comboBox_CreateRoomFlag->setEditable(true);
    ui->comboBox_CreateRoomFlag->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_CreateRoomFlag->lineEdit()->setReadOnly(true);
    //设置QComBobox的下拉框中的标签文字居中
    //static_cast<QStandardItemModel*>(ui->comboBox_CreateRoomFlag->model())->item(pos)->setTextAlignment(Qt::AlignCenter);
    ui->comboBox_CreateRoomFlag->addItem("经典大富翁模式");
    ui->comboBox_CreateRoomFlag->hide();
    ui->pushButton_CreateRoomShow->hide();
    ui->pushButton_CreateRoomBack->hide();


}

Game_MainPage::~Game_MainPage()
{
    delete client_init;
    client_init=NULL;
    delete ui;
}

void Game_MainPage::SetPage()
{
    this->setFixedSize(1400,900);
    ui->textEdit_chat->setStyleSheet("background-color: rgb(255, 255, 255, 60);");

    connect(&timer_recvfromServe, &QTimer::timeout,[=]()
    {
        RecvFrom_Serve();
    });

    connect(&timer_ParseMsg, &QTimer::timeout,[=]()
    {
        timer_ParseMsg.stop();
        ParseMegFromServe();
    });

    connect(&timer_recv_To_PrepareReadyPage, &QTimer::timeout,[=]()
            {
                Show_ReadyPage();
            });


    Recv_data.reserve(128);
    this->ui->pushButton_13->hide();
    this->ui->pushButton_13->setEnabled(false);
    ui->lineEdit_ChatmsgMychat->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    ui->lineEdit_Chatmsg1->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatmsg2->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatmsg3->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatmsg4->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatmsg5->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatmsg6->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    ui->lineEdit_Chatname1->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatname2->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatname3->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatname4->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatname5->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit_Chatname6->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    ui->pushButton_StratGame->setStyleSheet(QString("border-image:url(:/Building/Building (81).jpg);color:rgb(0,0,0);border-radius:100px;"));
    ui->pushButton_StratGame->setText(QString("开始游戏"));



    connect(ui->lineEdit_ChatmsgMychat, SIGNAL(returnPressed()), ui->pushButton_SendChatmsg, SLOT(click()), Qt::UniqueConnection);

    SetSliderStep();
    connect(ui->verticalSlider,SIGNAL(valueChanged(int)),this,SLOT(SliderValueChanged(int)));
    SetHide();
    //ReadChatInfo();


    slider_pos=ui->verticalSlider->sliderPosition();
    player=new Player;
    Set_ChatMsg_Page();


    ui->lineEdit_ChatmsgMychat->hide();
    ui->pushButton_SendChatmsg->hide();
}

void Game_MainPage::SetRoomPage()
{
    QPalette pal = ui->textEdit_StartRoom->palette();

    // 设置画刷，填充背景图片，且调整了图片大小
    pal.setBrush(QPalette::Base, QPixmap(":/Building/Building (83).png").scaled(ui->textEdit_StartRoom->size()));
    // 取消继承父类的背景样式
    ui->textEdit_StartRoom->setAutoFillBackground(true);
    // QTextEdit设置调色板，即填充了背景图片
    ui->textEdit_StartRoom->setPalette(pal);

}

void Game_MainPage::SetHide()
{
    ui->textEdit_chat->hide();
    ui->pushButton_ChatTouxiang1->hide();
    ui->pushButton_ChatTouxiang2->hide();
    ui->pushButton_ChatTouxiang3->hide();
    ui->pushButton_ChatTouxiang4->hide();
    ui->pushButton_ChatTouxiang1_2->hide();
    ui->pushButton_ChatTouxiang2_2->hide();
    ui->pushButton_ChatTouxiang3_2->hide();
    ui->pushButton_ChatTouxiang4_2->hide();

    ui->pushButton_ChatTouxiang5->hide();
    ui->pushButton_ChatTouxiang5_2->hide();
    ui->pushButton_ChatTouxiang6->hide();
    ui->pushButton_ChatTouxiang6_2->hide();

    ui->lineEdit_Chatmsg1->hide();
    ui->lineEdit_Chatmsg2->hide();
    ui->lineEdit_Chatmsg3->hide();
    ui->lineEdit_Chatmsg4->hide();
    ui->lineEdit_Chatmsg5->hide();
    ui->lineEdit_Chatmsg6->hide();

    ui->lineEdit_Chatname1->hide();
    ui->lineEdit_Chatname2->hide();
    ui->lineEdit_Chatname3->hide();
    ui->lineEdit_Chatname4->hide();
    ui->lineEdit_Chatname5->hide();
    ui->lineEdit_Chatname6->hide();

    ui->verticalSlider->hide();



}

void Game_MainPage::Set_ChatMsg_Page()
{
    SetHide();
    if(vector_ChatMsg_World.size()<=0)
    {
        ui->lineEdit_ChatmsgMychat->show();
        ui->pushButton_SendChatmsg->show();
        return;
    }
    QPushButton*btn_temp;

    if(vector_ChatMsg_World[pos_ChatMsg_World]->Get_chat_user()==ui->label_name->text().toUtf8())
    {
        ui->lineEdit_Chatmsg1->setAlignment(Qt::AlignRight);
        ui->pushButton_ChatTouxiang1->setIcon(QIcon(""));
        btn_temp= ui->pushButton_ChatTouxiang1_2;
    }
    else
    {
        ui->lineEdit_Chatmsg1->setAlignment(Qt::AlignLeft);
        btn_temp=ui->pushButton_ChatTouxiang1;
        ui->pushButton_ChatTouxiang1_2->setIcon(QIcon(""));
        ui->lineEdit_Chatname1->show();
        ui->lineEdit_Chatname1->setText(vector_ChatMsg_World[pos_ChatMsg_World]->Get_chat_user());
    }

    btn_temp->show();
    btn_temp->setStyleSheet("QPushButton{border:Opx}");
    btn_temp->setIconSize(QSize(45,45));
    btn_temp->setIcon(QPixmap(QString(":/Role/Role_%1.png").arg(vector_ChatMsg_World[pos_ChatMsg_World]->Get_chat_touxiang())));
    ui->lineEdit_Chatmsg1->setText(vector_ChatMsg_World[pos_ChatMsg_World]->Get_chat_content());
    ui->lineEdit_Chatmsg1->show();
    if(vector_ChatMsg_World.size()<=1)
    {
        ui->lineEdit_ChatmsgMychat->show();
        ui->pushButton_SendChatmsg->show();
        return;
    }

    if(vector_ChatMsg_World[pos_ChatMsg_World+1]->Get_chat_user()==ui->label_name->text().toUtf8())
    {
        ui->lineEdit_Chatmsg2->setAlignment(Qt::AlignRight);
        ui->pushButton_ChatTouxiang2->setIcon(QIcon(""));
        btn_temp= ui->pushButton_ChatTouxiang2_2;
    }
    else
    {
        ui->lineEdit_Chatmsg2->setAlignment(Qt::AlignLeft);
        ui->pushButton_ChatTouxiang2_2->setIcon(QIcon(""));
        btn_temp=ui->pushButton_ChatTouxiang2;
        ui->lineEdit_Chatname2->show();
        ui->lineEdit_Chatname2->setText(vector_ChatMsg_World[pos_ChatMsg_World+1]->Get_chat_user());
    }
    btn_temp->show();
    btn_temp->setStyleSheet("QPushButton{border:Opx}");
    btn_temp->setIconSize(QSize(45,45));
    btn_temp->setIcon(QPixmap(QString(":/Role/Role_%1.png").arg(vector_ChatMsg_World[pos_ChatMsg_World+1]->Get_chat_touxiang())));
    ui->lineEdit_Chatmsg2->setText(vector_ChatMsg_World[pos_ChatMsg_World+1]->Get_chat_content());
    ui->lineEdit_Chatmsg2->show();

    if(vector_ChatMsg_World.size()<=2)
    {
        ui->lineEdit_ChatmsgMychat->show();
        ui->pushButton_SendChatmsg->show();
        return;
    }
    if(vector_ChatMsg_World[pos_ChatMsg_World+2]->Get_chat_user()==ui->label_name->text().toUtf8())
    {
        ui->lineEdit_Chatmsg3->setAlignment(Qt::AlignRight);
        ui->lineEdit_Chatmsg3->setAlignment(Qt::AlignRight);
        ui->pushButton_ChatTouxiang3->setIcon(QIcon(""));
        btn_temp= ui->pushButton_ChatTouxiang3_2;
    }
    else
    {
        ui->lineEdit_Chatmsg3->setAlignment(Qt::AlignLeft);
        ui->pushButton_ChatTouxiang3_2->setIcon(QIcon(""));
        btn_temp=ui->pushButton_ChatTouxiang3;
        ui->lineEdit_Chatname3->show();
        ui->lineEdit_Chatname3->setText(vector_ChatMsg_World[pos_ChatMsg_World+2]->Get_chat_user());
    }
    btn_temp->show();
    btn_temp->setStyleSheet("QPushButton{border:Opx}");
    btn_temp->setIconSize(QSize(45,45));
    btn_temp->setIcon(QPixmap(QString(":/Role/Role_%1.png").arg(vector_ChatMsg_World[pos_ChatMsg_World+2]->Get_chat_touxiang())));
    ui->lineEdit_Chatmsg3->setText(vector_ChatMsg_World[pos_ChatMsg_World+2]->Get_chat_content());
    ui->lineEdit_Chatmsg3->show();

    if(vector_ChatMsg_World.size()<=3)
    {
        ui->lineEdit_ChatmsgMychat->show();
        ui->pushButton_SendChatmsg->show();
        return;
    }
    if(vector_ChatMsg_World[pos_ChatMsg_World+3]->Get_chat_user()==ui->label_name->text().toUtf8())
    {
        ui->lineEdit_Chatmsg4->setAlignment(Qt::AlignRight);
        ui->pushButton_ChatTouxiang4->setIcon(QIcon(""));
        btn_temp= ui->pushButton_ChatTouxiang4_2;
        ui->lineEdit_Chatmsg4->setAlignment(Qt::AlignRight);
    }
    else
    {
        ui->lineEdit_Chatmsg4->setAlignment(Qt::AlignLeft);
        ui->pushButton_ChatTouxiang4_2->setIcon(QIcon(""));
        btn_temp=ui->pushButton_ChatTouxiang4;
        ui->lineEdit_Chatname4->show();
        ui->lineEdit_Chatname4->setText(vector_ChatMsg_World[pos_ChatMsg_World+3]->Get_chat_user());
    }
    btn_temp->show();
    btn_temp->setStyleSheet("QPushButton{border:Opx}");
    btn_temp->setIconSize(QSize(45,45));
    btn_temp->setIcon(QPixmap(QString(":/Role/Role_%1.png").arg(vector_ChatMsg_World[pos_ChatMsg_World+3]->Get_chat_touxiang())));
    ui->lineEdit_Chatmsg4->setText(vector_ChatMsg_World[pos_ChatMsg_World+3]->Get_chat_content());
    ui->lineEdit_Chatmsg4->show();

    if(vector_ChatMsg_World.size()<=4)
    {
        ui->lineEdit_ChatmsgMychat->show();
        ui->pushButton_SendChatmsg->show();
        return;
    }
    if(vector_ChatMsg_World[pos_ChatMsg_World+4]->Get_chat_user()==ui->label_name->text().toUtf8())
    {
        ui->lineEdit_Chatmsg5->setAlignment(Qt::AlignRight);
        ui->pushButton_ChatTouxiang5->setIcon(QIcon(""));
        btn_temp= ui->pushButton_ChatTouxiang5_2;
        ui->lineEdit_Chatmsg5->setAlignment(Qt::AlignRight);
    }
    else
    {
        ui->lineEdit_Chatmsg5->setAlignment(Qt::AlignLeft);
        ui->pushButton_ChatTouxiang5_2->setIcon(QIcon(""));
        btn_temp=ui->pushButton_ChatTouxiang5;
        ui->lineEdit_Chatname5->show();
        ui->lineEdit_Chatname5->setText(vector_ChatMsg_World[pos_ChatMsg_World+4]->Get_chat_user());
    }
    btn_temp->show();
    btn_temp->setStyleSheet("QPushButton{border:Opx}");
    btn_temp->setIconSize(QSize(45,45));
    btn_temp->setIcon(QPixmap(QString(":/Role/Role_%1.png").arg(vector_ChatMsg_World[pos_ChatMsg_World+4]->Get_chat_touxiang())));
    ui->lineEdit_Chatmsg5->setText(vector_ChatMsg_World[pos_ChatMsg_World+4]->Get_chat_content());
    ui->lineEdit_Chatmsg5->show();

    if(vector_ChatMsg_World.size()<=5)
    {
        ui->lineEdit_ChatmsgMychat->show();
        ui->pushButton_SendChatmsg->show();
        return;
    }
    if(vector_ChatMsg_World[pos_ChatMsg_World+5]->Get_chat_user()==ui->label_name->text().toUtf8())
    {
        ui->lineEdit_Chatmsg6->setAlignment(Qt::AlignRight);
        ui->pushButton_ChatTouxiang6->setIcon(QIcon(""));
        btn_temp= ui->pushButton_ChatTouxiang6_2;
        ui->lineEdit_Chatmsg6->setAlignment(Qt::AlignRight);
    }
    else
    {
        ui->lineEdit_Chatmsg6->setAlignment(Qt::AlignLeft);
        ui->pushButton_ChatTouxiang6_2->setIcon(QIcon(""));
        btn_temp=ui->pushButton_ChatTouxiang6;
        ui->lineEdit_Chatname6->show();
        ui->lineEdit_Chatname6->setText(vector_ChatMsg_World[pos_ChatMsg_World+5]->Get_chat_user());
    }
    btn_temp->show();
    btn_temp->setStyleSheet("QPushButton{border:Opx}");
    btn_temp->setIconSize(QSize(45,45));
    btn_temp->setIcon(QPixmap(QString(":/Role/Role_%1.png").arg(vector_ChatMsg_World[pos_ChatMsg_World+5]->Get_chat_touxiang())));
    ui->lineEdit_Chatmsg6->setText(vector_ChatMsg_World[pos_ChatMsg_World+5]->Get_chat_content());
    ui->lineEdit_Chatmsg6->show();

    ui->verticalSlider->show();

}

int Game_MainPage::SetPageFromServe(QString u_name)
{
    if (client_init->waitForConnected(1000))//判断连接成功
    {
        QString Flag_num=QString("%1").arg(600);
        QString Send_data=Flag_num+" "+u_name;
        QByteArray sendbyteArray=Send_data.toUtf8();
        char *ch=sendbyteArray.data();
        qDebug()<<"ch=="<<ch;
        client_init->write(ch);

        Send_data.clear();
        sendbyteArray.clear();
        timer_recvfromServe.start(50);

    }
    else
    {
        QMessageBox::warning(this,"警告","2连接服务器失败,请点击确认后再次尝试 要获取更多信息请联系开发人员qq：1771132432");
        while(!client_init->waitForConnected(1000))
        {
            client_init=new QTcpSocket(this);
            client_init->connectToHost(QHostAddress("106.52.85.61"), 8989);
            if (client_init->waitForConnected(1000))//判断连接成功
            {
                QString Flag_num=QString("%1").arg(600);
                QString Send_data=Flag_num+" "+u_name;
                QByteArray sendbyteArray=Send_data.toUtf8();
                char *ch=sendbyteArray.data();
                qDebug()<<"ch=="<<ch;
                client_init->write(ch);

                Send_data.clear();
                sendbyteArray.clear();
                timer_recvfromServe.start(50);
                break;
            }
        }

    }
    return 0;
}

void Game_MainPage::RecvFrom_Serve()
{
    if (!client_init->waitForConnected(1000))//判断连接成功
    {
        return;
    }
    Chat_Msg_data.append(client_init->readAll());
    qDebug()<<"temp_data===="<<Chat_Msg_data<<Qt::endl;

    Chat_Msg_list=Chat_Msg_data.split(" ");
    qDebug()<<"readAll读出的数据后temp_list.size=="<<Chat_Msg_list.size();
    if(Chat_Msg_list.size()>=2)
    {
        if(Chat_Msg_list.size()==Chat_Msg_list[1].toInt())
        {     
            qDebug()<<"接受的数组大小和封装好的大小一致，开始处理";
            timer_ParseMsg.start(1);
        }
    }
    return;
}

int Game_MainPage::ParseMegFromServe()
{
    timer_ParseMsg.stop();
    int ret=-1;

    switch(Chat_Msg_list[0].toInt())
    {
    case 600:
        if(ParseMegFromServe_Setpage(Chat_Msg_list)==1)
        {
            qDebug()<<"处理日常界面成功";
            MsgParseStatus=true;
            qDebug()<<"MsgParseStatus=="<<MsgParseStatus;
        };
        break;
    case 667:
        ParseMegFromServe_chat(Chat_Msg_list);
        break;
    case 669:
        Parse_New_MegFromServe_chat(Chat_Msg_list);
        break;
    case 101:
        Recv_Aes_Key(Chat_Msg_list);
        break;
    case 112:
        Turn_To_ReadyPage(Chat_Msg_list);
        break;

    default:

        break;
    }
    Chat_Msg_data.clear();
    Chat_Msg_list.clear();
    return ret;
}

int Game_MainPage::ParseMegFromServe_Setpage(QStringList Msg)
{
    //flag为600，获取info信息的数组为6
    player->SetPlayer(Msg[2],Msg[3].toInt(),Msg[4].toInt(),Msg[5].toInt(),Msg[6].toInt());
    qDebug()<<"Player.name=="<<player->getName();
    this->ui->label_name->setText(player->getName());
    this->ui->label_level->setText(QString("等级：%1").arg(player->getLevel()));
    this->ui->label_Gold->setText(QString("金币数：%1").arg(player->getGoldnum()));
    this->ui->pushButton_Dianquan->setText(QString("点券数：%1").arg(player->getDianquan()));

    this->ui->pushButton_Touxiang->setStyleSheet("QPushButton{border:Opx}");
    this->ui->pushButton_Touxiang->setIconSize(QSize(100,100));
    this->ui->pushButton_Touxiang->setIcon(QPixmap(QString(":/Role/Role_%1.png").arg(player->getTouxiangflag())));

    return 1;

}

int Game_MainPage::Parse_New_MegFromServe_chat(QStringList Msg)
{
    if(vector_ChatMsg_World.size()==Chat_Msg_list[2].toInt())
    {
        return -1;
    }
    else
    {
        ParseMegFromServe_chat(Msg);
        return 1;
    }
}

int Game_MainPage::ParseMegFromServe_chat(QStringList Msg)
{
    if(Msg[2]=="MessageOver")
    {
        Status_SendMessage=true;
        ui->pushButton_SendChatmsg->setEnabled(true);
        ui->pushButton_ShowChatMsg->setEnabled(true);
        return 0;
    }
    //flag为600，获取chat信息的数组为9
    ChatMsg_World *charMsg_world=new ChatMsg_World;
    QDate _date;
    _date.setDate(Msg[6].toInt(),Msg[7].toInt(),Msg[8].toInt());

    charMsg_world->SetChatMsg(Msg[2].toInt(),Msg[3],Msg[4],Msg[5].toInt(),_date);
    vector_ChatMsg_World.append(charMsg_world);
    SetSliderStep();

    if(vector_ChatMsg_World.size()>=6)
    {
        pos_ChatMsg_World=vector_ChatMsg_World.size()-6;
    }
    Set_ChatMsg_Page();
    return 0;
}

void Game_MainPage::PullAllMsg()
{
    if (!client_init->waitForConnected(1000))//判断连接成功
    {
        return;
    }
    Status_SendMessage=false;
    QString Flag_num=QString("%1").arg(667);
    QString Msg_num=QString("%1").arg(vector_ChatMsg_World.size());
    QString Send_data=Flag_num+" "+Msg_num+" "+"拉取聊天信息";
    QByteArray sendbyteArray=Send_data.toUtf8();
    char *ch=sendbyteArray.data();
    qDebug()<<"ch=="<<ch;
    client_init->write(ch);

}

int Game_MainPage::SendMyChatMessage(QString Msg)
{
    int ret=0;
    if(Status_SendMessage)
    {
        if (!client_init->waitForConnected(1000))//判断连接成功
        {
            ret =-1;
        }
        else
        {
            QString Flag_num=QString("%1").arg(669);
            QString Msg_num=QString("%1").arg(vector_ChatMsg_World.size()+1);
            QString User_name=ui->label_name->text();
            QString Chat_content=ui->lineEdit_ChatmsgMychat->text();
            QString Chat_touxiang=QString("%1").arg(player->getTouxiangflag());

            QDate _date;
            _date.setDate(0,0,0);
            QString Chat_date=_date.toString("yyyy mm dd");
            QString Send_data=Flag_num+" "+Msg_num+" "+User_name+" "+Chat_content+" "+Chat_touxiang;
            ChatMsg_World * chatmsg_temp=new ChatMsg_World;
            chatmsg_temp->SetChatMsg(vector_ChatMsg_World.size()+1,User_name,Chat_content,player->getTouxiangflag(),_date);

            vector_ChatMsg_World.append(chatmsg_temp);

            if(vector_ChatMsg_World.size()>=6)
            {
                pos_ChatMsg_World=vector_ChatMsg_World.size()-6;
            }
            SetSliderStep();
            Set_ChatMsg_Page();

            QByteArray sendbyteArray=Send_data.toUtf8();
            char *ch=sendbyteArray.data();
            qDebug()<<"ch=="<<ch;
            client_init->write(ch);
            ui->lineEdit_ChatmsgMychat->clear();
            ret=1;
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","当前正在同步消息，请稍后重试！");
        ret=-1;
    }
    return ret;
}

void Game_MainPage::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPixmap pix(":/Building/Building (50).jpg");
    paint.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Game_MainPage::showEvent(QShowEvent *event)
{

}

void Game_MainPage::ReadChatInfo()
{
    QFile file("ChatInfo.txt");
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        qDebug()<<"打开ChatInfo.txt失败";
        return;
    }
    while(!file.atEnd())
    {
        if(file.atEnd())
        {
            break;
        }
        QString line;
        line = file.readLine();
        QStringList linelist=line.split(" ");
        if(linelist.size()<0)
        {
            qDebug()<<"linelist为空";
            return;
        }
        QDate date;
        date.setDate(linelist[3].toInt(),linelist[4].toInt(),linelist[5].toInt());
        ChatMsg_World *chatmsg_tmp=new ChatMsg_World;
        chatmsg_tmp->SetChatMsg(0,linelist[0],linelist[1],linelist[2].toInt(),date);
        vector_ChatMsg_World.append(chatmsg_tmp);
        SetSliderStep();
    }
}

void Game_MainPage::closeEvent(QCloseEvent *event)
{
//    delete client_init;
//    client_init=NULL;
}

void Game_MainPage::on_pushButton_ShowChatMsg_clicked()
{
    if(ui->pushButton_ShowChatMsg->text()=="收起消息")
    {
        if(Status_SendMessage)
        {
            SetHide();
            ui->lineEdit_ChatmsgMychat->hide();
            ui->pushButton_SendChatmsg->hide();
            ui->pushButton_ShowChatMsg->setText("显示消息");
        }
       else
        {
            QMessageBox::warning(this,"警告","请耐心等待本次消息同步完成，稍后再尝试折叠消息");
            ui->pushButton_ShowChatMsg->setEnabled(false);
            return;
        }

    }
    else
    {
        ui->pushButton_ShowChatMsg->setText("收起消息");
        PullAllMsg();

        Set_ChatMsg_Page();
        ui->pushButton_SendChatmsg->show();
        ui->lineEdit_ChatmsgMychat->show();
    }
}

void Game_MainPage::on_pushButton_SendChatmsg_clicked()
{
    ui->pushButton_SendChatmsg->setEnabled(false);
    if(ui->lineEdit_ChatmsgMychat->text().size()<=0)
    {
        ui->pushButton_SendChatmsg->setEnabled(true);
        return;
    }
    if(ui->lineEdit_ChatmsgMychat->text()=="说点什么吧")
    {
        QMessageBox::warning(this,"警告","太没新意了吧！换句话试试吧！");
        ui->pushButton_SendChatmsg->setEnabled(true);
        return;
    }
    if(SendMyChatMessage(ui->lineEdit_ChatmsgMychat->text())==1)
    {
        ui->pushButton_SendChatmsg->setEnabled(true);
        Sleep(1);
        return;
    }
}
void Game_MainPage::SetSliderStep()
{
    ui->verticalSlider->setMinimum(0);
    if(vector_ChatMsg_World.size()<6)
    {
        ui->verticalSlider->setMaximum(0);
        return;
    }
    ui->verticalSlider->setMaximum(vector_ChatMsg_World.size());
    ui->verticalSlider->setSingleStep(1);
    ui->verticalSlider->setValue(1);
}

void Game_MainPage::Btn_Move_up(QPushButton *btn)
{
    int x=btn->geometry().x();
    int y=btn->geometry().y();
    btn->move(x,y-3);
}

void Game_MainPage::Btn_Move_down(QPushButton *btn)
{
    int x=btn->geometry().x();
    int y=btn->geometry().y();
    btn->move(x,y+3);

}

void Game_MainPage::Secret_Key_Negotiation()
{
    MyRsa*myrsa=new MyRsa();
    myrsa->Create();
    myrsa->Write_Pri();
    myrsa->Write_Pub();
    string pubkey=myrsa->Read_RPub_To_String();
    myrsa->Read_RPub_FromString(pubkey);

    string encontent=myrsa->Get_encrypt_Value_Pub(string("你好"));
    int encontentsize=0;encontentsize=encontent.size();

    MyprotobufRsakeyStruct *RsakeyStruct=new MyprotobufRsakeyStruct;//(101,encontentsize,pubkey,encontent);
    RsakeyStruct->flag=101;
    RsakeyStruct->size=encontentsize;
    qDebug()<<"encontentsize=="<<encontentsize;
    RsakeyStruct->RsaKey=pubkey;
    RsakeyStruct->encontent=encontent;
    RsakeyStruct->Hashcontent=myrsa->My_RSA_sign("你好");

    MyProrobuf * myproto=new MyprotobufRsakey;
    dynamic_cast<MyprotobufRsakey*>(myproto)->initMessage(RsakeyStruct);
    string sendencodemsg=dynamic_cast<MyprotobufRsakey*>(myproto)->encodeMsg();
    string senddata="101 "+plaintext_to_binary(sendencodemsg.c_str(),sendencodemsg.size());

   //测试序列化
    dafuwenprotobuf::Protobuf_RsaPubKey proto_rsapubk=*(dafuwenprotobuf::Protobuf_RsaPubKey*) dynamic_cast<MyprotobufRsakey*>(myproto)->decodeMsg(sendencodemsg);
    cout << " proto_rsapubk->flag" << proto_rsapubk.flag() << endl;
    cout << " proto_rsapubk->encontentsize" << proto_rsapubk.encontentsize() << endl;
    cout << " proto_rsapubk->pubkey" << proto_rsapubk.pubkey() << endl;
    cout << " proto_rsapubk->encontent" << proto_rsapubk.encontent() << endl;
    cout << " proto_rsapubk->Hashcontent" << proto_rsapubk.hashcontent() << endl;

    char * ch=new char[4096];
    ch=(char *)senddata.c_str();

    qDebug()<<"ch=="<<ch;

    if(client_init->waitForConnected(1000))
    {
        client_init->write(ch);
    }
    myrsa->Read_RPub_FromString(proto_rsapubk.pubkey());
    cout<<"读取的公钥为"<<myrsa->Read_RPub_To_String();
    string decontent=myrsa->Get_decrypt_Value_Pri(encontent);
    qDebug()<<decontent.c_str();
}

int Game_MainPage::Recv_Aes_Key(QStringList Msg)
{
    int ret=0;

    QString str = Msg[2];
    QByteArray utf8Bytes = str.toUtf8();
    char* ch=new char[1024];
    ch= utf8Bytes.data();
    qDebug()<<"ch=="<<ch;

    MyProrobuf* myprotobuf = new MyprotobufRsakey;

    dafuwenprotobuf::Protobuf_RsaPubKey *proto_rsapubk=new dafuwenprotobuf::Protobuf_RsaPubKey;
       proto_rsapubk= (dafuwenprotobuf::Protobuf_RsaPubKey*)
                                                         dynamic_cast<MyprotobufRsakey*>(myprotobuf)->decodeMsg(binary_to_plaintext(ch));//binary_to_plaintext(ch)

    cout << " proto_rsapubk->encontent : " << proto_rsapubk->encontent() << endl;
    Room_id=proto_rsapubk->flag();//服务器返回时用flag代替了room_id,这里只是为了发回这个数，并无其他意思
    MyRsa *myrsa=new MyRsa;
    myrsa->Read_Pri();
    The_Aes_Key= myrsa->Get_decrypt_Value_Pri(proto_rsapubk->encontent());

    qDebug()<<"对称秘钥aesuserkey=="<<The_Aes_Key.c_str();
                                          if(Room_id>=0)
    {
        Send_Create_Room_Info();
    }

    return ret;
}

void Game_MainPage::SliderValueChanged(int value)
{
    qDebug()<<"SliderValueChanged";
    qDebug()<<"slider pos=="<<ui->verticalSlider->sliderPosition();

    if(ui->verticalSlider->sliderPosition()>=6)
    {
        pos_ChatMsg_World=vector_ChatMsg_World.size()-ui->verticalSlider->sliderPosition();
    }

    qDebug()<<"pos_ChatMsg_World"<<pos_ChatMsg_World;

    Set_ChatMsg_Page();
}

void Game_MainPage::on_pushButton_StratGame_clicked()
{
    qDebug()<<"点击开始游戏";
    ui->pushButton_StratGame->setEnabled(false);
    SetRoomPage();
    ui->textEdit_StartRoom->show();
    ui->pushButton_CreateRoom->show();
    ui->pushButton_Join_Room->show();
    ui->pushButton_JoinRandomRoom->show();
    ui->pushButton_Room_back->show();
}

void Game_MainPage::on_pushButton_StratGame_pressed()
{
    Btn_Move_down(ui->pushButton_StratGame);
}

void Game_MainPage::on_pushButton_StratGame_released()
{
    Btn_Move_up(ui->pushButton_StratGame);
}

void Game_MainPage::on_pushButton_ShowChatMsg_pressed()
{
    Btn_Move_down(ui->pushButton_ShowChatMsg);
}

void Game_MainPage::on_pushButton_ShowChatMsg_released()
{
    Btn_Move_up(ui->pushButton_ShowChatMsg);
}

void Game_MainPage::on_pushButton_SendChatmsg_pressed()
{
    Btn_Move_down(ui->pushButton_SendChatmsg);
}

void Game_MainPage::on_pushButton_SendChatmsg_released()
{
    Btn_Move_up(ui->pushButton_SendChatmsg);
}

void Game_MainPage::on_pushButton_Room_back_clicked()
{
    ui->textEdit_StartRoom->hide();
    ui->pushButton_CreateRoom->hide();
    ui->pushButton_Join_Room->hide();
    ui->pushButton_JoinRandomRoom->hide();
    ui->pushButton_Room_back->hide();
    ui->pushButton_StratGame->setEnabled(true);
}

void Game_MainPage::on_pushButton_Room_back_pressed()
{
    Btn_Move_down(ui->pushButton_Room_back);
}

void Game_MainPage::on_pushButton_Room_back_released()
{
    Btn_Move_up(ui->pushButton_Room_back);
}

void Game_MainPage::on_pushButton_CreateRoom_clicked()//点击建房按钮
{

    ui->pushButton_CreateRoom->hide();
    ui->pushButton_Join_Room->hide();
    ui->pushButton_JoinRandomRoom->hide();
    ui->pushButton_Room_back->hide();

    ui->label_CreateRoomName->show();
    ui->label_CreateRoomFlag->show();
    ui->label_CreateRoomPasswd->show();
    ui->label_CreateRoomDescription->show();
    ui->lineEdit_CreateRoom->show();
    ui->lineEdit_CreateRoomPasswd->show();
    ui->lineEdit_CreateRoomDescription->show();
    ui->comboBox_CreateRoomFlag->show();
    ui->pushButton_CreateRoomShow->show();
    ui->pushButton_CreateRoomBack->show();
}

void Game_MainPage::on_pushButton_CreateRoomBack_clicked()
{

    ui->pushButton_CreateRoom->show();
    ui->pushButton_Join_Room->show();
    ui->pushButton_JoinRandomRoom->show();
    ui->pushButton_Room_back->show();

    ui->label_CreateRoomName->hide();
    ui->label_CreateRoomFlag->hide();
    ui->label_CreateRoomPasswd->hide();
    ui->label_CreateRoomDescription->hide();
    ui->lineEdit_CreateRoom->hide();
    ui->lineEdit_CreateRoomPasswd->hide();
    ui->lineEdit_CreateRoomDescription->hide();
    ui->comboBox_CreateRoomFlag->hide();
    ui->pushButton_CreateRoomShow->hide();
    ui->pushButton_CreateRoomBack->hide();
}

void Game_MainPage::on_pushButton_CreateRoomShow_clicked()//点击确认后进去准备页面
{
    ui->pushButton_CreateRoomShow->setEnabled(false);
    if(ui->lineEdit_CreateRoom->text().size()<=0)
    {
        QMessageBox::warning(this,"警告","请输入待创建房间的名称");
        ui->pushButton_CreateRoomShow->setEnabled(true);
        return;
    }
    Secret_Key_Negotiation();
//    game_ready_page=new Game_Ready_Page;
//    game_ready_page->SetPage_FromServe(ui->label_name->text());

    //这里加一个Qtimer，启动判断game_ready_page 中一个状态flag为真再显示
//    this->close();
//     game_ready_page->show();
//    delete this;
}

void Game_MainPage::on_pushButton_CreateRoomShow_pressed()
{
    Btn_Move_down(ui->pushButton_CreateRoomShow);
}

void Game_MainPage::on_pushButton_CreateRoomShow_released()
{
    Btn_Move_up(ui->pushButton_CreateRoomShow);
}

void Game_MainPage::Send_Create_Room_Info()
{
    MyprotobufRoomReadyInfoStruct *RoomReadyInfoStruct=new MyprotobufRoomReadyInfoStruct;

    RoomReadyInfoStruct->Room_ID=Room_id;
    RoomReadyInfoStruct->Room_Name=ui->lineEdit_CreateRoom->text().toStdString();
    RoomReadyInfoStruct->Room_Description=ui->lineEdit_CreateRoomDescription->text().toStdString();

    RoomReadyInfoStruct->Room_Flag=ui->comboBox_CreateRoomFlag->currentText().toInt();

    /*换算密码hash值*/
    QCryptographicHash hash_creator(QCryptographicHash::Sha256);
    /*设置源数据，生成hash数据*/
    hash_creator.addData(ui->lineEdit_CreateRoomPasswd->text().toUtf8());
    RoomReadyInfoStruct->Room_Pwd = QString(hash_creator.result().toHex()).toStdString(); //szPassword变成密码hash值了

    RoomReadyInfoStruct->Player_Order=1;
    RoomReadyInfoStruct->Player_Name=player->getName().toStdString();
    RoomReadyInfoStruct->Player_TouxiangFlag=player->getTouxiangflag();

    MyProtobufRoomReadyInfo *ProtobufRoomReadyInfo=new MyProtobufRoomReadyInfo;
    ProtobufRoomReadyInfo->initMessage(RoomReadyInfoStruct);
    std::string roomInfo=ProtobufRoomReadyInfo->encodeMsg();
    qDebug()<<"序列化后的字符串为："<<roomInfo.c_str();

   MyAes myaes(The_Aes_Key.c_str());
   std::string En_roomInfo=myaes.Aes_Encode(roomInfo);

   int len=roomInfo.size()+1;
   qDebug()<<"strlen(Binary_roomInfo.c_str())+1："<<len;

   std::string De_roomInfo=myaes.Aes_Decode(En_roomInfo);

   qDebug()<<"一系列变化后的字符串为："<<De_roomInfo.c_str();
   if(roomInfo==De_roomInfo)
   {
        qDebug()<<"序列化加密成功";
   }
   else
   {
        qDebug()<<"序列化加密失败";
   }

   MyProtobufRoomReadyInfo *ProtobufRoomReadyInfo2=new MyProtobufRoomReadyInfo;
   Room_Info* RoomInfoStruct = (Room_Info*)ProtobufRoomReadyInfo2->decodeMsg(De_roomInfo);
   cout<<"RoomInfoStruct->room_name().c_str() : "<< RoomInfoStruct->room_name().c_str() << endl;
   cout << "RoomInfoStruct->room_description().c_str() : " << RoomInfoStruct->room_description().c_str() << endl;
   cout << "RoomInfoStruct->room_pwd().c_str() : " << RoomInfoStruct->room_pwd().c_str() << endl;
   cout << "RoomInfoStruct->player_name().c_str() : " << RoomInfoStruct->player_name().c_str() << endl;
   cout << "  RoomInfoStruct->player_touxiangflag() : "<< RoomInfoStruct->player_touxiangflag() << endl;

   std::string binaryEn_roomInfo=plaintext_to_binary(En_roomInfo.c_str(),En_roomInfo.size());
   std::string sendData;

   sendData="111 "+to_string(Room_id)+" "+to_string(len)+" "+binaryEn_roomInfo;
   qDebug()<<"sendData.size()=="<<sendData.size();
   qDebug()<<"sendData=="<<sendData.c_str();
   if(client_init->waitForConnected(1000))
   {
        client_init->write(sendData.c_str());
   }

}

void Game_MainPage::Turn_To_ReadyPage(QStringList Msg)
{
   if(Msg[2]=="Ready")
   {
        game_ready_page=new Game_Ready_Page();
         timer_recv_To_PrepareReadyPage.start(1);
        game_ready_page->SetPage_FromServe(player->getName());
        qDebug()<<"准备页面开始设置";
   }
   else
   {
        QMessageBox::warning(this,"警告","创建/加入房间失败，请重试");
        qDebug()<<"创建/加入房间失败";
   }

}

void Game_MainPage::Show_ReadyPage()
{
   if(game_ready_page->ReadyPageStatus)
   {
        timer_recv_To_PrepareReadyPage.stop();
        game_ready_page->show();
        this->close();
   }
   else
   {
        qDebug()<<"game_ready_page->ReadyPageStatus=="<<game_ready_page->ReadyPageStatus;
        return;
   }
}
