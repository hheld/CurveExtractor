#include "FittedCurveGraphicsItem.h"

#include <QPainter>

FittedCurveGraphicsItem::FittedCurveGraphicsItem(const QVector<double> &curveDataX, const QVector<double> &curveDataY, QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    numOfDataPoints = curveDataX.size();

    Q_ASSERT(numOfDataPoints == curveDataY.size());

    for(int i=0; i<numOfDataPoints; ++i)
    {
        points << QPointF(curveDataX[i], curveDataY[i]);
    }
}

FittedCurveGraphicsItem::~FittedCurveGraphicsItem()
{
}

void FittedCurveGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::green);
    pen.setWidthF(0.);

    painter->setPen(pen);

    painter->drawPolyline(points);
}

QRectF FittedCurveGraphicsItem::boundingRect() const
{
    return points.boundingRect();
}
