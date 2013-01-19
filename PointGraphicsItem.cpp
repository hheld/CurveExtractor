#include "PointGraphicsItem.h"

#include <QPen>
#include <QPainter>

PointGraphicsItem::PointGraphicsItem(const QPointF &center, const QString &toolTip, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    color(Qt::magenta),
    center(center),
    radius(2.)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);

    setToolTip(toolTip);
}

PointGraphicsItem::~PointGraphicsItem()
{
}

void PointGraphicsItem::setColor(const QColor &color)
{
    this->color = color;
}

void PointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(color);
    pen.setWidthF(0.1);

    painter->setPen(pen);

    painter->drawEllipse(center, radius, radius);
    painter->drawLine(QPointF(center.x(), center.y()-radius), QPointF(center.x(), center.y()+radius));
    painter->drawLine(QPointF(center.x()-radius, center.y()), QPointF(center.x()+radius, center.y()));
}

QRectF PointGraphicsItem::boundingRect() const
{
    QPointF dim(radius, radius);

    return QRectF(center - dim, center + dim);
}
