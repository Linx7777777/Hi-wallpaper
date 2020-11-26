#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QtNetwork>
#include <DMainWindow>
#include <DLineEdit>
#include <DFrame>
#include <DPushButton>
#include <DLabel>
DWIDGET_BEGIN_NAMESPACE
class MainWindow:public DMainWindow
{
Q_OBJECT
public:
    void initUI();
    void initConnection();
    void initData();
    MainWindow(QWidget *parent=nullptr);
public Q_SLOTS:
    void slotDownload(bool clicked);
    void slotShowImage(QNetworkReply *reply);
private:
    DLineEdit *textEdit=nullptr;
    DPushButton *getBtn=nullptr;
    DFrame *showFrame=nullptr;
    DLabel *showLabel=nullptr;
    QNetworkAccessManager *manager=nullptr;
    QNetworkRequest request;
};
DWIDGET_END_NAMESPACE
#endif // MAINWINDOW_H
