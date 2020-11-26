#include "pictureitem.h"
#include <QGraphicsScene>
DWIDGET_USE_NAMESPACE

PictureItem::PictureItem(QGraphicsItem *parent):QGraphicsPixmapItem (parent)
{
   m_menu=new DMenu("yoyoyo");
   downloadAction=new QAction("下载图片");
   wallpaperAction=new QAction ("设置为壁纸");
   clearAction=new QAction ("清除");
   m_menu->addAction(downloadAction);
   m_menu->addAction(wallpaperAction);
   m_menu->addAction(clearAction);
   initConnection();
}

void PictureItem::initConnection()
{
    QObject::connect(m_menu,&DMenu::triggered,this,[=](QAction *action){
        if(action->text()=="下载图片"){
           Q_EMIT this->sigDownloadPic();
        }else if(action->text()=="设置为壁纸") {
           Q_EMIT this->sigSetWallpaper();
        }else {
            this->hide();
        }
    });
}

PictureItem::~PictureItem()
{
    delete m_menu;
}

void PictureItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::RightButton){
        if(m_menu->isHidden()){
        }
            m_menu->setGeometry(QCursor::pos().x(),QCursor::pos().y(),100,100);
            m_menu->exec();
    }
    return QGraphicsPixmapItem::mouseMoveEvent(event);
}
