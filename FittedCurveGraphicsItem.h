#ifndef FITTEDCURVEGRAPHICSITEM_H
#define FITTEDCURVEGRAPHICSITEM_H

#include <QGraphicsItem>

class FittedCurveGraphicsItem : public QGraphicsItem
{
public:
    FittedCurveGraphicsItem(const QVector<double> &curveDataX, const QVector<double> &curveDataY, QGraphicsItem *parent = 0);
    ~FittedCurveGraphicsItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    QPolygonF points;
    int numOfDataPoints;
};

#endif // FITTEDCURVEGRAPHICSITEM_H
