/********************************************************************************
** Form generated from reading UI file 'create_user.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATE_USER_H
#define UI_CREATE_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Create_User
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *UserName;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *PassWord;
    QLineEdit *VerifyPwd;
    QLineEdit *lineEdit_2;
    QLabel *label_5;

    void setupUi(QMainWindow *Create_User)
    {
        if (Create_User->objectName().isEmpty())
            Create_User->setObjectName("Create_User");
        Create_User->resize(433, 310);
        centralwidget = new QWidget(Create_User);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        UserName = new QLineEdit(centralwidget);
        UserName->setObjectName("UserName");
        UserName->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(UserName, 0, 1, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 5, 0, 1, 2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        PassWord = new QLineEdit(centralwidget);
        PassWord->setObjectName("PassWord");
        PassWord->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(PassWord, 1, 1, 1, 1);

        VerifyPwd = new QLineEdit(centralwidget);
        VerifyPwd->setObjectName("VerifyPwd");
        VerifyPwd->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(VerifyPwd, 2, 1, 1, 1);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout->addWidget(lineEdit_2, 3, 1, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        Create_User->setCentralWidget(centralwidget);

        retranslateUi(Create_User);

        QMetaObject::connectSlotsByName(Create_User);
    } // setupUi

    void retranslateUi(QMainWindow *Create_User)
    {
        Create_User->setWindowTitle(QCoreApplication::translate("Create_User", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("Create_User", "\350\257\267\344\270\272\350\264\246\345\217\267\350\256\276\347\275\256\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("Create_User", "\346\263\250\345\206\214", nullptr));
        label_3->setText(QCoreApplication::translate("Create_User", "\350\257\267\345\206\215\346\254\241\350\276\223\345\205\245\345\257\206\347\240\201\347\241\256\350\256\244", nullptr));
        label->setText(QCoreApplication::translate("Create_User", "\350\257\267\350\276\223\345\205\245\350\246\201\346\263\250\345\206\214\347\232\204\346\211\213\346\234\272\345\217\267\346\210\226\351\202\256\347\256\261", nullptr));
        label_5->setText(QCoreApplication::translate("Create_User", "\350\257\267\350\276\223\345\205\245\346\224\266\345\210\260\347\232\204\351\252\214\350\257\201\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Create_User: public Ui_Create_User {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATE_USER_H
