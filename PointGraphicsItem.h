#ifndef POINTGRAPHICSITEM_H
#define POINTGRAPHICSITEM_H

#include <QGraphicsItem>

class MeasurementAreaLineItem;

class PointGraphicsItem : public QGraphicsItem
{
public:
    PointGraphicsItem(const QPointF &center, const QString &toolTip, bool sendPositionChanges = false, QGraphicsItem *parent = 0);
    ~PointGraphicsItem();

    void setColor(const QColor &color);
    QColor getColor() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setConnectedMeasurementLineItem(MeasurementAreaLineItem *connectedLine);

private:
    QColor color;
    QPointF center;
    double radius;
    MeasurementAreaLineItem *connectedMeasurementLineItem;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // POINTGRAPHICSITEM_H
