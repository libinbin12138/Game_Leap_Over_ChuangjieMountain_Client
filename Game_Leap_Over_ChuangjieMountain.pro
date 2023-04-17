#-------------------------------------------------
#
# Project created by QtCreator 2023-02-25T16:15:13
#
#-------------------------------------------------

QT       += core gui network core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game_Leap_Over_ChuangjieMountain
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES +=PROTOBUF_USE_DLLS

SOURCES += \
    MyAes.cpp \
    MyRsa.cpp \
    dafuwen.pb.cc \
        main.cpp \
        mainwindow.cpp \
    myprorobuf.cpp \
    myprotobufroomreadyinfo.cpp \
    myprotobufrsakey.cpp \
    playscreen.cpp \
    building_info_dialog.cpp \
    building_info.cpp \
    game_ready_page.cpp \
    log_in.cpp \
    create_user.cpp \
    game_mainpage.cpp \
    player.cpp \
    chatmsg_world.cpp

HEADERS += \
    MyAes.h \
    MyRsa.h \
    dafuwen.pb.h \
        mainwindow.h \
    myprorobuf.h \
    myprotobufroomreadyinfo.h \
    myprotobufrsakey.h \
    playscreen.h \
    building_info_dialog.h \
    building_info.h \
    game_ready_page.h \
    log_in.h \
    create_user.h \
    game_mainpage.h \
    player.h \
    chatmsg_world.h

FORMS += \
        mainwindow.ui \
    playscreen.ui \
    building_info_dialog.ui \
    game_ready_page.ui \
    log_in.ui \
    create_user.ui \
    game_mainpage.ui

RESOURCES += \
    roll.qrc \
    role.qrc \
    building.qrc \
    arrow.qrc

    INCLUDEPATH += "C:\Program Files\OpenSSL-Win64\include"
    LIBS += "C:\Program Files\OpenSSL-Win64\lib\libssl.lib"
    LIBS += "C:\Program Files\OpenSSL-Win64\lib\libcrypto.lib"

INCLUDEPATH += "C:\Program Files\proto_buf_3.21\include"
LIBS += "C:\Program Files\proto_buf_3.21\lib\libprotobufd.lib"
LIBS += "C:\Program Files\proto_buf_3.21\lib\libprotocd.lib"
CONFIG += resources_big

DISTFILES += \
    dafuwen.proto
