/*  CurveExtractor A simple tool to extract data points from images.
 *  Copyright (c) 2013, Harald Held <harald.held@gmail.com>
 *  All rights reserved.
 *  https://bitbucket.org/hheld/curveextractor
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *  (1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *
 *  (3) The name of the author may not be used to
 *      endorse or promote products derived from this software without
 *      specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

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
