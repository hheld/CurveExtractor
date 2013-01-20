#include "MeasurementAreaLineItem.h"

#include <QPainter>
#include <QDebug>

MeasurementAreaLineItem::MeasurementAreaLineItem(QGraphicsItem *endItem1, QGraphicsItem *endItem2, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    endItem1(endItem1),
    endItem2(endItem2)
{
    pen.setColor(Qt::gray);
    pen.setWidthF(0.);
}

void MeasurementAreaLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(endItem1 && endItem2)
    {
        painter->setPen(pen);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawLine(endItem1->scenePos(), endItem2->scenePos());
    }
}

QRectF MeasurementAreaLineItem::boundingRect() const
{
    if(endItem1 && endItem2)
    {
        QPointF end1 = endItem1->scenePos();
        QPointF end2 = endItem2->scenePos();

        qreal minX = end1.x() < end2.x() ? end1.x() : end2.x();
        qreal minY = end1.y() < end2.y() ? end1.y() : end2.y();
        qreal maxX = end1.x() > end2.x() ? end1.x() : end2.x();
        qreal maxY = end1.y() > end2.y() ? end1.y() : end2.y();

        return QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
    }

    return QRectF();
}

void MeasurementAreaLineItem::setColor(const QColor &color)
{
    pen.setColor(color);
}

void MeasurementAreaLineItem::endPointChangedPosition()
{
    prepareGeometryChange();
}
