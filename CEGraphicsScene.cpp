#include "CEGraphicsScene.h"
#include "PointGraphicsItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

CEGraphicsScene::CEGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

CEGraphicsScene::~CEGraphicsScene()
{
}

void CEGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF origin = event->scenePos();

    PointGraphicsItem *pgi = new PointGraphicsItem(origin, tr("Data point"));
    pgi->setColor(Qt::blue);

    addItem(pgi);
}
