/********************************************************************************
** Form generated from reading UI file 'log_in.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_IN_H
#define UI_LOG_IN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Log_In
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLineEdit *Username;
    QLabel *label_2;
    QLineEdit *Pwd;
    QLabel *label;
    QPushButton *pushButton_login;
    QPushButton *pushButton_create;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Log_In)
    {
        if (Log_In->objectName().isEmpty())
            Log_In->setObjectName("Log_In");
        Log_In->resize(766, 491);
        centralwidget = new QWidget(Log_In);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        Username = new QLineEdit(centralwidget);
        Username->setObjectName("Username");
        Username->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Username, 0, 1, 1, 2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        Pwd = new QLineEdit(centralwidget);
        Pwd->setObjectName("Pwd");
        Pwd->setEchoMode(QLineEdit::Password);
        Pwd->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Pwd, 1, 1, 1, 2);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton_login = new QPushButton(centralwidget);
        pushButton_login->setObjectName("pushButton_login");

        gridLayout->addWidget(pushButton_login, 8, 1, 1, 2);

        pushButton_create = new QPushButton(centralwidget);
        pushButton_create->setObjectName("pushButton_create");

        gridLayout->addWidget(pushButton_create, 8, 0, 1, 1);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit, 3, 2, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 3, 0, 1, 1);

        Log_In->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Log_In);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 766, 17));
        Log_In->setMenuBar(menubar);
        statusbar = new QStatusBar(Log_In);
        statusbar->setObjectName("statusbar");
        Log_In->setStatusBar(statusbar);

        retranslateUi(Log_In);

        QMetaObject::connectSlotsByName(Log_In);
    } // setupUi

    void retranslateUi(QMainWindow *Log_In)
    {
        Log_In->setWindowTitle(QCoreApplication::translate("Log_In", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("Log_In", "\347\216\251\345\256\266\345\257\206\347\240\201 \357\274\232", nullptr));
        label->setText(QCoreApplication::translate("Log_In", "\347\216\251\345\256\266\350\264\246\345\217\267 \357\274\232", nullptr));
        pushButton_login->setText(QCoreApplication::translate("Log_In", "\347\231\273\345\275\225", nullptr));
        pushButton_create->setText(QCoreApplication::translate("Log_In", "\346\263\250\345\206\214", nullptr));
        lineEdit->setText(QCoreApplication::translate("Log_In", "\350\257\267\345\234\250\346\255\244\345\244\204\350\276\223\345\205\245\346\270\270\346\210\217\345\206\205\346\265\213\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("Log_In", "\345\277\230\350\256\260\345\257\206\347\240\201\350\257\267\347\202\271\350\277\231\351\207\214\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Log_In: public Ui_Log_In {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_IN_H
