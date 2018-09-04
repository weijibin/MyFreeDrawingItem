#ifndef FREEDRAWINGITEM_H
#define FREEDRAWINGITEM_H

#include <QGraphicsItem>
#include "anchorpointinfo.h"
#include "customitem.h"
#include "anchorpointitem.h"

class FreeDrawingItem: public QGraphicsItem
{
public:
    FreeDrawingItem(QGraphicsItem *parent);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QVector<QPainterPath> m_subPaths;
    QVector<QGraphicsPathItem> m_subPathItems;

    QVector<AnchorPointInfo> m_AnchorPoints;
    QVector<AnchorPointItem> m_AnchorPointItems;
};

#endif // FREEDRAWINGITEM_H
