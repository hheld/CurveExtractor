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
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void positionUpdated(PointGraphicsItem *pgi);

    void setOriginItem(PointGraphicsItem *oi);
    void setTopLeftItem(PointGraphicsItem *tli);
    void setBottomRightItem(PointGraphicsItem *bri);
    void removeItem(PointGraphicsItem *pgi);

    QVector<double> getXData() const;
    QVector<double> getYData() const;

signals:
    void itemDataRemoved(PointGraphicsItem *pgi);
    void pointAdded();
    void pointRemoved();
    
public slots:
    void onAddDataPoint(double x, double y, PointGraphicsItem *pgi);
    void onOriginChanged(double x, double y);
    void onTopLeftChanged(double x, double y);
    void onBottomrightChanged(double x, double y);
    
private:
    QList<QPointF> absolutePoints;
    QList<QPointF> points;
    QList<PointGraphicsItem*> pgis;

    QPointF origin;
    QPointF topLeft;
    QPointF bottomRight;

    PointGraphicsItem *originItem;
    PointGraphicsItem *topLeftItem;
    PointGraphicsItem *bottomRightItem;
};

#endif // SELECTEDPOINTSTABLEMODEL_H
