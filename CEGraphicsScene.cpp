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

void CEGraphicsScene::onUpdateOriginCoords(double x, double y)
{
    origin.setX(x);
    origin.setY(y);
}

void CEGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    origin = event->scenePos();

    PointGraphicsItem *pgi = new PointGraphicsItem(origin, tr("Data point"));
    pgi->setColor(Qt::blue);

    addItem(pgi);
}
