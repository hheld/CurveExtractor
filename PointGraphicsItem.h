#ifndef POINTGRAPHICSITEM_H
#define POINTGRAPHICSITEM_H

#include <QGraphicsItem>

class MeasurementAreaLineItem;
class SelectedPointsTableModel;

class PointGraphicsItem : public QGraphicsItem
{
public:
    PointGraphicsItem(const QPointF &center, const QString &toolTip, QGraphicsItem *parent = 0);
    ~PointGraphicsItem();

    void setColor(const QColor &color);
    QColor getColor() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setConnectedMeasurementLineItem(MeasurementAreaLineItem *connectedLine);
    void setModel(SelectedPointsTableModel *model);

private:
    QColor color;
    QPointF center;
    double radius;
    MeasurementAreaLineItem *connectedMeasurementLineItem;
    SelectedPointsTableModel *model;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // POINTGRAPHICSITEM_H
