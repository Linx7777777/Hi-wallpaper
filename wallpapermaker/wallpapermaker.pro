QT += core gui network concurrent dbus
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wallpapermaker
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    pictureitem.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    mainwindow.h \
    pictureitem.h
