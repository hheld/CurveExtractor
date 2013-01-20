#include "CEGraphicsView.h"
#include "CEGraphicsScene.h"

#include <QWheelEvent>
#include <QGraphicsPixmapItem>

CEGraphicsView::CEGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    theScene(new CEGraphicsScene),
    showImg(true),
    bgItem(0)
{
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

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

    if(!bgPixmap.isNull())
    {
        if(bgItem)
        {
            theScene->removeItem(bgItem);
            delete bgItem;
        }

        bgItem = new QGraphicsPixmapItem(bgPixmap);
        bgItem->setZValue(-1.);

        theScene->addItem(bgItem);

        fitBgImgInView();
    }
}

void CEGraphicsView::fitBgImgInView()
{
    theScene->setSceneRect(theScene->itemsBoundingRect());

    if(!bgPixmap.isNull())
    {
        fitInView(bgPixmap.rect(), Qt::KeepAspectRatio);
    }
}

void CEGraphicsView::onShowImgChanged(bool showImg)
{
    this->showImg = showImg;

    if(bgItem)
    {
        bgItem->setVisible(showImg);
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
