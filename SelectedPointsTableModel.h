#ifndef SELECTEDPOINTSTABLEMODEL_H
#define SELECTEDPOINTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QPointF>

class PointGraphicsItem;

class SelectedPointsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SelectedPointsTableModel(QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void positionUpdated(PointGraphicsItem *pgi);

signals:
    
public slots:
    void onAddDataPoint(double x, double y, PointGraphicsItem *pgi);
    
private:
    QList<QPointF> absolutePoints;
    QList<QPointF> points;
    QList<PointGraphicsItem*> pgis;
};

#endif // SELECTEDPOINTSTABLEMODEL_H
