#ifndef CREATE_USER_H
#define CREATE_USER_H

#include <QMainWindow>
#include<QTcpSocket>
#include<QTimer>
class Log_In;

namespace Ui {
class Create_User;
}

class Create_User : public QMainWindow
{
    Q_OBJECT

public:
    explicit Create_User(QWidget *parent = 0);
    ~Create_User();
protected:
    void RecvFrom_Serve();
    void ParseMegFromServe();
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_clicked();
   // void Verify_Input();
private:
    Ui::Create_User *ui;
    Log_In *login_in;

    QTcpSocket * client;
    QByteArray Recv_data;
    QTimer timer_ReadFromServe;
    QTimer timer_ParseMsg;
};

#endif // CREATE_USER_H
