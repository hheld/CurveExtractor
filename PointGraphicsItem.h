#ifndef POINTGRAPHICSITEM_H
#define POINTGRAPHICSITEM_H

#include <QGraphicsItem>

class PointGraphicsItem : public QGraphicsItem
{
public:
    PointGraphicsItem(const QPointF &center, const QString &toolTip, QGraphicsItem *parent = 0);
    ~PointGraphicsItem();

    void setColor(const QColor &color);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QColor color;
    QPointF center;
    double radius;
};

#endif // POINTGRAPHICSITEM_H
