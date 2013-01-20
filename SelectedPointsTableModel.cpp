#include "SelectedPointsTableModel.h"
#include "PointGraphicsItem.h"

#include <QDebug>

SelectedPointsTableModel::SelectedPointsTableModel(QObject *parent) :
    QAbstractTableModel(parent),
    originItem(0),
    topLeftItem(0),
    bottomRightItem(0)
{
}

int SelectedPointsTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return points.size();
}

int SelectedPointsTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant SelectedPointsTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        int r = index.row();
        int c = index.column();

        QPointF oi(0., 0.);
        QPointF tli(0., 0.);
        QPointF bri(0., 0.);

        if(originItem)
        {
            oi = originItem->scenePos();
        }

        if(topLeftItem)
        {
            tli = topLeftItem->scenePos();
        }

        if(bottomRightItem)
        {
            bri = bottomRightItem->scenePos();
        }

        switch(c)
        {
        case 0:
            return origin.x() + (points.at(r).x() - oi.x()) / (bri.x() - oi.x()) * (bottomRight.x() - origin.x());
            break;
        case 1:
            return origin.y() + (points.at(r).y() - oi.y()) / (tli.y() - oi.y()) * (topLeft.y() - origin.y());
            break;
        }
    }

    return QVariant();
}

bool SelectedPointsTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for(int i=0; i<count; ++i)
    {
        absolutePoints.append(QPointF(0., 0.));
        points.append(QPointF(0., 0.));
        pgis.append(0);
    }

    endInsertRows();

    return true;
}

bool SelectedPointsTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count -1);

    for(int i=row+count-1; i>=row; --i)
    {
        points.removeAt(i);
        absolutePoints.removeAt(i);
        pgis.removeAt(i);
    }

    endRemoveRows();

    return true;
}

QVariant SelectedPointsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return tr("x");
                break;
            case 1:
                return tr("y");
                break;
            }
        }
        else
        {
            return section + 1;
        }
    }

    return QVariant();
}

void SelectedPointsTableModel::positionUpdated(PointGraphicsItem *pgi)
{
    int i = pgis.indexOf(pgi);

    if(i > -1)
    {
        points[i] = absolutePoints[i] + pgi->scenePos();

        emit dataChanged(index(i, 0), index(i, 1));
    }
    else if(pgi == originItem)
    {
        emit dataChanged(index(0, 0), index(points.size()-1, 1));
    }
}

void SelectedPointsTableModel::setOriginItem(PointGraphicsItem *oi)
{
    originItem = oi;
}

void SelectedPointsTableModel::setTopLeftItem(PointGraphicsItem *tli)
{
    topLeftItem = tli;
}

void SelectedPointsTableModel::setBottomRightItem(PointGraphicsItem *bri)
{
    bottomRightItem = bri;
}

void SelectedPointsTableModel::onAddDataPoint(double x, double y, PointGraphicsItem *pgi)
{
    insertRow(points.size());

    int i = points.size() - 1;

    pgis.last() = pgi;

    points[i].setX(x);
    points[i].setY(y);

    absolutePoints[i].setX(x);
    absolutePoints[i].setY(y);
}

void SelectedPointsTableModel::onOriginChanged(double x, double y)
{
    origin.setX(x);
    origin.setY(y);

    emit dataChanged(index(0, 0), index(points.size()-1, 1));
}

void SelectedPointsTableModel::onTopLeftChanged(double x, double y)
{
    topLeft.setX(x);
    topLeft.setY(y);

    emit dataChanged(index(0, 0), index(points.size()-1, 1));
}

void SelectedPointsTableModel::onBottomrightChanged(double x, double y)
{
    bottomRight.setX(x);
    bottomRight.setY(y);

    emit dataChanged(index(0, 0), index(points.size()-1, 1));
}
