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

#include "PointGraphicsItem.h"
#include "MeasurementAreaLineItem.h"
#include "SelectedPointsTableModel.h"

#include <QPen>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QObject>
#include <QDebug>

PointGraphicsItem::PointGraphicsItem(const QPointF &center, const QString &toolTip, bool isMeasurementPoint, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    isMeasurementPoint(isMeasurementPoint),
    color(Qt::magenta),
    center(center),
    radius(2.),
    connectedMeasurementLineItem(0),
    model(0)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    setToolTip(toolTip);
}

PointGraphicsItem::~PointGraphicsItem()
{
}

void PointGraphicsItem::setColor(const QColor &color)
{
    this->color = color;
}

QColor PointGraphicsItem::getColor() const
{
    return color;
}

void PointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(color);
    pen.setWidthF(0.5);

    painter->setPen(pen);

    painter->drawEllipse(center, radius, radius);

    pen.setWidthF(0.);
    painter->setPen(pen);

    painter->drawLine(QPointF(center.x(), center.y()-radius), QPointF(center.x(), center.y()+radius));
    painter->drawLine(QPointF(center.x()-radius, center.y()), QPointF(center.x()+radius, center.y()));
}

QRectF PointGraphicsItem::boundingRect() const
{
    QPointF dim(radius, radius);

    return QRectF(center - dim, center + dim);
}

void PointGraphicsItem::setConnectedMeasurementLineItem(MeasurementAreaLineItem *connectedLine)
{
    connectedMeasurementLineItem = connectedLine;
}

void PointGraphicsItem::setModel(SelectedPointsTableModel *model)
{
    this->model = model;
}

QVariant PointGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(connectedMeasurementLineItem && change == ItemScenePositionHasChanged)
    {
        connectedMeasurementLineItem->endPointChangedPosition();
    }

    if(model && change == ItemScenePositionHasChanged)
    {
        model->positionUpdated(this);
    }

    return QGraphicsItem::itemChange(change, value);
}

void PointGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(!isMeasurementPoint)
    {
        QMenu menu;

        QAction *a = menu.addAction(QObject::tr("Remove point"));

        if(menu.exec(event->screenPos()) == a)
        {
            model->removeItem(this);
        }
    }
}
