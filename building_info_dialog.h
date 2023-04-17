#ifndef BUILDING_INFO_DIALOG_H
#define BUILDING_INFO_DIALOG_H

#include <QDialog>
#include<QList>
#include"building_info.h"

namespace Ui {
class Building_Info_Dialog;
}

class Building_Info_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Building_Info_Dialog(QWidget *parent = 0);
    ~Building_Info_Dialog();
    void paintEvent(QPaintEvent *event);

    void Read_Building_info();
    void SetLineEditContent(int num);
    void SetLineEditContent_From_serve(int num, QString Username, int Grade);
    void ClearLineEditContent();
protected:

private:
    Ui::Building_Info_Dialog *ui;

    QList<Building_Info*>Building_info_list;
};

#endif // BUILDING_INFO_DIALOG_H
