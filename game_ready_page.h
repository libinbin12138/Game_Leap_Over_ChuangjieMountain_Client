#ifndef GAME_READY_PAGE_H
#define GAME_READY_PAGE_H

#include <QMainWindow>
#include<QTcpSocket>

#include<playscreen.h>
#include<QTimer>

namespace Ui {
class Game_Ready_Page;
}

class Game_Ready_Page : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_Ready_Page(QWidget *parent = 0);
    ~Game_Ready_Page();
    void SetPage_FromServe(QString uname);

    bool ReadyPageStatus;
protected:
    void paintEvent(QPaintEvent *event);
    void Init_Page();
    void HideChatMsg();
    int SetChatMsg();
    int RecvData();
    std::string *SendDataSet(int flag,std::string content);
private slots:
    void on_pushButton_ShowChatMsg_clicked();

    void on_pushButton_SendChatmsg_clicked();

private:
    Ui::Game_Ready_Page *ui;

     QTcpSocket *client;

     PlayScreen playsereen;

     QTimer StartGame_timer;
};

#endif // GAME_READY_PAGE_H
