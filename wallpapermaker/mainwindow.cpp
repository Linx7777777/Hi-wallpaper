#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <DMessageBox>
#include <QDebug>
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
    textEdit->setFixedSize(this->width(),50);
    showFrame=new DFrame;
    showFrame->setFrameRounded(true);
    showLabel=new DLabel(showFrame);
    showLabel->setFixedSize(showFrame->width(),showFrame->height());
    QHBoxLayout *frameLayout=new QHBoxLayout;
    showFrame->setLayout(frameLayout);
    frameLayout->addWidget(showLabel);
    btnlayout->addWidget(getBtn);
    btnlayout->addWidget(preBtn);
    btnlayout->addWidget(nextBtn);
    mainlayout->addWidget(textEdit);
    mainlayout->addLayout(btnlayout);
    mainlayout->addWidget(showLabel);
    widget->setLayout(mainlayout);
    setCentralWidget(widget);
}

void MainWindow::initConnection()
{
    QObject::connect(getBtn,SIGNAL(clicked(bool)),this,SLOT(slotDownload(bool)));
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slotShowImage(QNetworkReply *)));
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

void MainWindow::slotDownload(bool clicked)
{
    Q_UNUSED(clicked);
    QUrl url;
      QString address=textEdit->text();
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
        QByteArray data_bytes = reply->readAll();
        QPixmap* cur_pictrue =new QPixmap();
        cur_pictrue->loadFromData(data_bytes);
        cur_pictrue->scaled(showLabel->width(),showLabel->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        showLabel->setPixmap(*cur_pictrue);
}
}
