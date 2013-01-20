#ifndef MEASUREMENTAREALINEITEM_H
#define MEASUREMENTAREALINEITEM_H

#include <QGraphicsItem>
#include <QPen>

class MeasurementAreaLineItem : public QGraphicsItem
{
public:
    MeasurementAreaLineItem(QGraphicsItem *endItem1, QGraphicsItem *endItem2, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setColor(const QColor &color);

    void endPointChangedPosition();

private:
    QGraphicsItem *endItem1;
    QGraphicsItem *endItem2;

    QPen pen;
};

#endif // MEASUREMENTAREALINEITEM_H
