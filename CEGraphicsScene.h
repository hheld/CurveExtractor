#ifndef CEGRAPHICSSCENE_H
#define CEGRAPHICSSCENE_H

#include <QGraphicsScene>

class PointGraphicsItem;
class SelectedPointsTableModel;

class CEGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CEGraphicsScene(QObject *parent = 0);
    ~CEGraphicsScene();

    void setModel(SelectedPointsTableModel *model);

signals:
    void pointAdded(double x, double y, PointGraphicsItem *pgi);
    
public slots:

private:
    SelectedPointsTableModel *model;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CEGRAPHICSSCENE_H
