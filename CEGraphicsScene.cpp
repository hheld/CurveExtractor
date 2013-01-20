#include "CEGraphicsScene.h"
#include "PointGraphicsItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

CEGraphicsScene::CEGraphicsScene(QObject *parent) :
    QGraphicsScene(parent),
    model(0)
{
}

CEGraphicsScene::~CEGraphicsScene()
{
}

void CEGraphicsScene::setModel(SelectedPointsTableModel *model)
{
    this->model = model;
}

void CEGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF origin = event->scenePos();

    PointGraphicsItem *pgi = new PointGraphicsItem(origin, tr("Data point"));
    pgi->setColor(Qt::blue);
    pgi->setModel(model);

    addItem(pgi);

    emit pointAdded(origin.x(), origin.y(), pgi);
}


void CEGraphicsScene::onDataPointRemoved(PointGraphicsItem *pgi)
{
    removeItem(pgi);
    delete pgi;
}
