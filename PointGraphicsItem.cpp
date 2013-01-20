#include "PointGraphicsItem.h"
#include "MeasurementAreaLineItem.h"
#include "SelectedPointsTableModel.h"

#include <QPen>
#include <QPainter>
#include <QDebug>

PointGraphicsItem::PointGraphicsItem(const QPointF &center, const QString &toolTip, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    color(Qt::magenta),
    center(center),
    radius(2.),
    connectedMeasurementLineItem(0),
    model(0)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    setToolTip(toolTip);
}

PointGraphicsItem::~PointGraphicsItem()
{
}

void PointGraphicsItem::setColor(const QColor &color)
{
    this->color = color;
}

QColor PointGraphicsItem::getColor() const
{
    return color;
}

void PointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(color);
    pen.setWidthF(0.5);

    painter->setPen(pen);

    painter->drawEllipse(center, radius, radius);

    pen.setWidthF(0.);
    painter->setPen(pen);

    painter->drawLine(QPointF(center.x(), center.y()-radius), QPointF(center.x(), center.y()+radius));
    painter->drawLine(QPointF(center.x()-radius, center.y()), QPointF(center.x()+radius, center.y()));
}

QRectF PointGraphicsItem::boundingRect() const
{
    QPointF dim(radius, radius);

    return QRectF(center - dim, center + dim);
}

void PointGraphicsItem::setConnectedMeasurementLineItem(MeasurementAreaLineItem *connectedLine)
{
    connectedMeasurementLineItem = connectedLine;
}

void PointGraphicsItem::setModel(SelectedPointsTableModel *model)
{
    this->model = model;
}

QVariant PointGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(connectedMeasurementLineItem && change == ItemScenePositionHasChanged)
    {
        connectedMeasurementLineItem->endPointChangedPosition();
    }

    if(model && change == ItemScenePositionHasChanged)
    {
        model->positionUpdated(this);
    }

    return QGraphicsItem::itemChange(change, value);
}
