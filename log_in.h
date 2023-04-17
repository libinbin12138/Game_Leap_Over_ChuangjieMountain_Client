#ifndef LOG_IN_H
#define LOG_IN_H
#include<QLabel>
#include<QLineEdit>
#include <QMainWindow>
#include<QTimer>
#include<QTcpSocket>


class Create_User;
class Game_MainPage;

namespace Ui {
class Log_In;
}

class Log_In : public QMainWindow
{
    Q_OBJECT

public:
    explicit Log_In(QWidget *parent = 0);
    ~Log_In();
protected:
    void RecvFrom_Serve();
    void ParseMegFromServe();
    void SetPage();
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void ShowGameMain();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_create_clicked();

private:
    Ui::Log_In *ui;
    Create_User *create_user;
    QLineEdit * LineEdit_Key;

    QTcpSocket * client;
    QByteArray Recv_data;
    QTimer timer_ReadFromServe;
    QTimer timer_ParseMsg;
    QTimer timer_gamemain;

    Game_MainPage *game_mainpage;
};

#endif // LOG_IN_H
