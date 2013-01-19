#include "CEGraphicsView.h"
#include "CEGraphicsScene.h"

#include <QWheelEvent>

CEGraphicsView::CEGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    theScene(new CEGraphicsScene)
{
    setScene(theScene);
}

CEGraphicsView::~CEGraphicsView()
{
    delete theScene;
}

void CEGraphicsView::setBackgroundImage(const QString &img)
{
    backgroundImgPath = img;
    bgPixmap.load(backgroundImgPath);
    theScene->setSceneRect(bgPixmap.rect());
}

void CEGraphicsView::fitBgImgInView()
{
    if(!bgPixmap.isNull())
    {
        fitInView(bgPixmap.rect(), Qt::KeepAspectRatio);
    }
}

void CEGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if(!bgPixmap.isNull())
    {
        painter->drawPixmap(0, 0, bgPixmap);
    }
}

void CEGraphicsView::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if(delta>0)
    {
        scale(1.1, 1.1);
    }
    else
    {
        scale(0.9, 0.9);
    }
}
