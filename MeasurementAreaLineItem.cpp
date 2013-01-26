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

#include "MeasurementAreaLineItem.h"

#include <QPainter>
#include <QDebug>

MeasurementAreaLineItem::MeasurementAreaLineItem(QGraphicsItem *endItem1, QGraphicsItem *endItem2, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    endItem1(endItem1),
    endItem2(endItem2)
{
    pen.setColor(Qt::gray);
    pen.setWidthF(0.);
}

void MeasurementAreaLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(endItem1 && endItem2)
    {
        painter->setPen(pen);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawLine(endItem1->scenePos(), endItem2->scenePos());
    }
}

QRectF MeasurementAreaLineItem::boundingRect() const
{
    if(endItem1 && endItem2)
    {
        QPointF end1 = endItem1->scenePos();
        QPointF end2 = endItem2->scenePos();

        qreal minX = end1.x() < end2.x() ? end1.x() : end2.x();
        qreal minY = end1.y() < end2.y() ? end1.y() : end2.y();
        qreal maxX = end1.x() > end2.x() ? end1.x() : end2.x();
        qreal maxY = end1.y() > end2.y() ? end1.y() : end2.y();

        return QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
    }

    return QRectF();
}

void MeasurementAreaLineItem::setColor(const QColor &color)
{
    pen.setColor(color);
}

void MeasurementAreaLineItem::endPointChangedPosition()
{
    prepareGeometryChange();
}
