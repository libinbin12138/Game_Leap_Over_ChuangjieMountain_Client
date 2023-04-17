#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include <QWidget>
#include<QMainWindow>
#include <QTimer>
#include<QPushButton>
#include<QLabel>
#include<QVector>
#include<QMouseEvent>
#include<QList>

#include<QTcpSocket>


class Building_Info_Dialog;

namespace Ui {
class PlayScreen;
}

class PlayScreen : public QMainWindow
{
    Q_OBJECT
public:
    enum RollingStatus
    {
        Rolling=1,
        Rollfinish=2
    };
    explicit PlayScreen(QWidget *parent = 0);
    ~PlayScreen();

    void Set_Roll_Pushbutton_Icon(RollingStatus status);
    void Set_Roll();
    void Set_BUilding_Button();
    void SendData(int num);
private slots:
    void slot_recvmessage();
protected:
    void paintEvent(QPaintEvent *event);
    //    void enterEvent(QEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
private:
    Ui::PlayScreen *ui;

    float Old_Width,Old_height;

    float Building_Button_width,Building_Button_height;
    int label_Num;

    QPushButton *roll_btn;
    QPushButton *roll_btn2;
    QTimer timer_Rollstart;
    QTimer timer_finish;
    int Roll_num1,Roll_num2,Roll_final_num;

    QList<QPushButton*>Build_Button_list;
    Building_Info_Dialog *building_info_diag;
    QTcpSocket *client;
};

#endif // PLAYSCREEN_H
