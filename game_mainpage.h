#ifndef GAME_MAINPAGE_H
#define GAME_MAINPAGE_H

#include "game_ready_page.h"
#include <QMainWindow>
#include<QTcpSocket>
#include<QTimer>
#include<QStringList>
#include<QList>
#include<QVector>
#include<QPushButton>
class ChatMsg_World;
class Player;
class Game_Ready_Page;
namespace Ui {
class Game_MainPage;
}

typedef std::string  haha;
class Game_MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_MainPage(QWidget *parent = 0);
    ~Game_MainPage();
    int SetPageFromServe(QString u_name);
    void RecvFrom_Serve();
    int ParseMegFromServe();
    int ParseMegFromServe_Setpage(QStringList Msg);
    int Parse_New_MegFromServe_chat(QStringList Msg);
    int ParseMegFromServe_chat(QStringList Msg);
    bool MsgParseStatus;
    void PullAllMsg();
    int SendMyChatMessage(QString Msg);
protected:
    void SetPage();
    void SetRoomPage();
    void SetHide();
    void Set_ChatMsg_Page();
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void ReadChatInfo();
    void closeEvent(QCloseEvent *event);

    void SetSliderStep();
    void Btn_Move_up(QPushButton*btn);
    void Btn_Move_down(QPushButton*btn);

    void Secret_Key_Negotiation();

    int Recv_Aes_Key(QStringList Msg);

    void Send_Create_Room_Info();

    void Turn_To_ReadyPage(QStringList Msg);
    void Show_ReadyPage();
private slots:

    void on_pushButton_ShowChatMsg_clicked();

    void on_pushButton_SendChatmsg_clicked();

    void SliderValueChanged(int value);

    void on_pushButton_StratGame_clicked();

    void on_pushButton_StratGame_pressed();

    void on_pushButton_StratGame_released();

    void on_pushButton_ShowChatMsg_pressed();

    void on_pushButton_ShowChatMsg_released();

    void on_pushButton_SendChatmsg_pressed();

    void on_pushButton_SendChatmsg_released();

    void on_pushButton_Room_back_clicked();

    void on_pushButton_Room_back_pressed();

    void on_pushButton_Room_back_released();

    void on_pushButton_CreateRoom_clicked();

    void on_pushButton_CreateRoomBack_clicked();

    void on_pushButton_CreateRoomShow_clicked();

    void on_pushButton_CreateRoomShow_pressed();

    void on_pushButton_CreateRoomShow_released();


private:

    Ui::Game_MainPage *ui;

    QTcpSocket *client_init;

    QByteArray Recv_data;
    QStringList Chat_Msg_list;
    QString Chat_Msg_data;

    QTimer timer_recvfromServe;
    QTimer timer_ParseMsg;
    Player *player;

    QVector<ChatMsg_World*>vector_ChatMsg_World;
    int pos_ChatMsg_World;
    int slider_pos;
    bool Status_SendMessage;
    Game_Ready_Page *game_ready_page;

    int Room_id;
    haha The_Aes_Key;

     QTimer timer_recv_To_PrepareReadyPage;
};

#endif // GAME_MAINPAGE_H
