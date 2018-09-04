#-------------------------------------------------
#
# Project created by QtCreator 2018-08-30T14:13:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpServerMC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcp_server.cpp \
    tcp_server_private.cpp

HEADERS  += mainwindow.h \
    tcp_server.h \
    tcp_server_private.h

FORMS    += mainwindow.ui

CONFIG +=C++11
