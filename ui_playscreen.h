/********************************************************************************
** Form generated from reading UI file 'playscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYSCREEN_H
#define UI_PLAYSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayScreen
{
public:

    void setupUi(QWidget *PlayScreen)
    {
        if (PlayScreen->objectName().isEmpty())
            PlayScreen->setObjectName("PlayScreen");
        PlayScreen->resize(716, 300);

        retranslateUi(PlayScreen);

        QMetaObject::connectSlotsByName(PlayScreen);
    } // setupUi

    void retranslateUi(QWidget *PlayScreen)
    {
        PlayScreen->setWindowTitle(QCoreApplication::translate("PlayScreen", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayScreen: public Ui_PlayScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYSCREEN_H
