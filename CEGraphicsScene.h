#ifndef CEGRAPHICSSCENE_H
#define CEGRAPHICSSCENE_H

#include <QGraphicsScene>

class CEGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CEGraphicsScene(QObject *parent = 0);
    ~CEGraphicsScene();

signals:
    
public slots:
    void onUpdateOriginCoords(double x, double y);

private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    QPointF origin;
};

#endif // CEGRAPHICSSCENE_H
