#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <DMessageBox>
#include <QDebug>
#include <DFileDialog>
#include <QDir>
#include <QtConcurrent>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusPendingCall>
DWIDGET_USE_NAMESPACE

void MainWindow::initUI()
{
    QVBoxLayout *mainlayout=new QVBoxLayout (this);
    QHBoxLayout *btnlayout=new QHBoxLayout (this);
    auto widget=new QWidget (this);
    getBtn=new DPushButton ("下载图片");
    auto nextBtn=new DIconButton(DStyle::SP_ArrowNext);
    auto preBtn =new DIconButton(DStyle::SP_ArrowPrev);
    textEdit=new DLineEdit;
    QGraphicsView *m_view=new QGraphicsView (this);
    QGraphicsScene*m_scene=new QGraphicsScene (m_view);
    m_item=new PictureItem;
    m_scene->addItem(m_item);
    m_view->setScene(m_scene);
    btnlayout->addWidget(getBtn);
    btnlayout->addWidget(preBtn);
    btnlayout->addWidget(nextBtn);
    mainlayout->addWidget(textEdit);
    mainlayout->addLayout(btnlayout);
    mainlayout->addWidget(m_view);
    widget->setLayout(mainlayout);
    setCentralWidget(widget);
}

void MainWindow::initConnection()
{
    QObject::connect(getBtn,SIGNAL(clicked(bool)),this,SLOT(slotDownload(bool)));
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slotShowImage(QNetworkReply *)));
    QObject::connect(m_item,&PictureItem::sigDownloadPic,this,[=]{
        QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        desktopPath += QStringLiteral("/wallpapers");
        QDir dir(desktopPath);
        if(!dir.exists()){
           dir.mkpath(desktopPath);
        }
        QString str = DFileDialog::getSaveFileName(this,"保存图片",desktopPath, "图片文件");
        QPixmap *pictrue =new QPixmap;
        int a= address.lastIndexOf(".");
        pictrue->loadFromData(data_bytes);
        QString suffix=address.mid(a+1,address.length()-1);
        const QString fileName=str+QStringLiteral(".")+suffix;
        QFileInfo info(fileName);
        QtConcurrent::run(QThreadPool::globalInstance(),[pictrue, fileName,suffix]{
            pictrue->save(fileName,suffix.toLatin1());
          });
    });
    QObject::connect(m_item,&PictureItem::sigSetWallpaper,this,[=]{
        QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        desktopPath += QStringLiteral("/wallpapers/");
        QDir dir(desktopPath);
        if(!dir.exists()){
           dir.mkpath(desktopPath);
        }
        QPixmap *pictrue =new QPixmap;
        int a= address.lastIndexOf(".");
        pictrue->loadFromData(data_bytes);
        int b=address.lastIndexOf("/");
        QString suffix=address.mid(a+1,address.length()-1);
        const QString fileName=desktopPath+address.mid(b+1,address.length()-1);
        QFileInfo info(fileName);
        QtConcurrent::run(QThreadPool::globalInstance(),[pictrue, fileName,suffix]{
            pictrue->save(fileName,suffix.toLatin1());
          });
        QDBusInterface *interface = new QDBusInterface("com.deepin.daemon.Appearance", "/com/deepin/daemon/Appearance",
                                        "com.deepin.daemon.Appearance", QDBusConnection::sessionBus());
        qInfo()<<interface->isValid();
        QDBusMessage mess= interface->call("Set", "background",fileName);
    qInfo()<<mess.errorMessage();
    });
}

void MainWindow::initData()
{
    manager=new QNetworkAccessManager (this);
}

MainWindow::MainWindow(QWidget *parent):DMainWindow (parent)
{
    initUI();
    initData();
    initConnection();

}

MainWindow::~MainWindow()
{
    delete cur_pictrue;
}

void MainWindow::slotDownload(bool clicked)
{
    Q_UNUSED(clicked);
    QUrl url;
    address=textEdit->text();
    url=QUrl(address);
    request.setPriority(QNetworkRequest::HighPriority);
    request.setUrl(url);
    manager->get(request);

}

void MainWindow::slotShowImage(QNetworkReply *reply)
{
    QVariant nCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qInfo()<<nCode;
    if(reply->error()!=QNetworkReply::NoError){
    QMessageBox *messageBox=new QMessageBox(QMessageBox::Warning,"Error","url is error",QMessageBox::Close|QMessageBox::Ok,this,Qt::Popup);
    messageBox->exec();
    }else {
        data_bytes = reply->readAll();
        cur_pictrue =new QPixmap;
        cur_pictrue->loadFromData(data_bytes);
        m_item->show();
        m_item->setPixmap(*cur_pictrue);
    }
}
