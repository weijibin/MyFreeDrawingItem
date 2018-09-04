#include "freedrawingitem.h"

FreeDrawingItem::FreeDrawingItem(QGraphicsItem *parent)
{

}

QRectF FreeDrawingItem::boundingRect() const
{
    QRectF rect = childrenBoundingRect();
    return rect;
}

void FreeDrawingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
