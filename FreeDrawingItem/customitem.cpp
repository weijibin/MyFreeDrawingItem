#include "customitem.h"
CustomItem::CustomItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{

}

QRectF CustomItem::boundingRect() const
{
    return getBoundingBox();
}

void CustomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
