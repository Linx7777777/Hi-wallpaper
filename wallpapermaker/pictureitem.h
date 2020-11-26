#ifndef PICTUREITEM_H
#define PICTUREITEM_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <DMenu>
#include <QAction>
#include <QGraphicsSceneEvent>
#include <QObject>
#include <QDebug>
DWIDGET_BEGIN_NAMESPACE
class PictureItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit PictureItem(QGraphicsItem *parent = nullptr);
    void initConnection();
    ~PictureItem();
signals:
    void sigDownloadPic();
    void sigSetWallpaper();
public slots:
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    DMenu *m_menu=nullptr;
    QAction *downloadAction;
    QAction *wallpaperAction;
    QAction *clearAction;
};
DWIDGET_END_NAMESPACE
#endif // PICTUREITEM_H
