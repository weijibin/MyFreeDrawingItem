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


// creating
void FreeDrawingItem::downWhenCreating(QPointF point)
{

}

void FreeDrawingItem::moveWhenCreating(QPointF point)
{

}

void FreeDrawingItem::upWhenCreating(QPointF point)
{

}

// end creating
void FreeDrawingItem::endCreate()
{

}

// editing
void FreeDrawingItem::downWhenEditing(QPointF point)
{

}

void FreeDrawingItem::moveWhenEditing(QPointF point)
{

}

void FreeDrawingItem::upWhenEditing(QPointF point)
{

}

// translate item  or  call in command
void FreeDrawingItem::translateItem(QPointF offset)
{

}

// add command
//    void addCommandToSlide(HHCommand * command);

// save
void FreeDrawingItem::getJSONObj( QJsonObject& jsonObj )
{

}

// restore
void FreeDrawingItem::fromJSONObj(QJsonObject& jsonObj )
{

}
