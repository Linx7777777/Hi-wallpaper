#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QtNetwork>
#include <DMainWindow>
#include <DLineEdit>
#include <DFrame>
#include <DPushButton>
#include <DLabel>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "pictureitem.h"
#include <DApplication>
#include <QCoreApplication>
#include <QGuiApplication>
#define dApp (static_cast<Application *>(QCoreApplication::instance()))

DWIDGET_BEGIN_NAMESPACE
class MainWindow:public DMainWindow
{
Q_OBJECT
public:
    void initUI();
    void initConnection();
    void initData();
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
public Q_SLOTS:
    void slotDownload(bool clicked);
    void slotShowImage(QNetworkReply *reply);
private:
    DLineEdit *textEdit=nullptr;
    DPushButton *getBtn=nullptr;
    DFrame *showFrame=nullptr;
    DLabel *showLabel=nullptr;
    QNetworkAccessManager *manager=nullptr;
    PictureItem *m_item=nullptr;
    QPixmap *cur_pictrue;
    QString address;
    QNetworkRequest request;
    QByteArray data_bytes;
};
DWIDGET_END_NAMESPACE
#endif // MAINWINDOW_H
