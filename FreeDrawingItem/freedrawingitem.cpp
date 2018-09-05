#include "freedrawingitem.h"
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QDebug>

FreeDrawingItem::FreeDrawingItem(QGraphicsItem *parent):QGraphicsItem(parent)
{
    m_subPaths.clear();
    m_AnchorPointItems.clear();
}

FreeDrawingItem::FreeDrawingItem(const FreeDrawingItem &item)
{

}

QRectF FreeDrawingItem::boundingRect() const
{
    QRectF rect = childrenBoundingRect();
    return rect;
}

void FreeDrawingItem::updateBoundingRect()
{
    prepareGeometryChange();
    m_boundingRect = childrenBoundingRect();
//    this->scene()->update();
}

void FreeDrawingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
//    painter->setPen(Qt::red);
//    painter->drawRect(boundingRect());
    painter->setPen(Qt::darkGreen);
    foreach (QPainterPath path, m_subPaths)
    {
        painter->drawPath(path);
    }
    painter->restore();
}

QPainterPath FreeDrawingItem::getPath()
{
    QPainterPath path;
    foreach (QPainterPath temp , m_subPaths) {
        path.addPath(temp);
    }
    return path;
}

//clone
FreeDrawingItem * FreeDrawingItem::clone()
{
    return new FreeDrawingItem(*this);
}


void FreeDrawingItem::startCreate(QPointF point)
{
    QPointF pos = point;

    AnchorPointItem * item = new AnchorPointItem(this);
    item->setAnchorPos(pos);

    m_AnchorPointItems.append(item);


    //next sub Path
    QPainterPath path;
    path.moveTo(pos);
    m_subPaths.append(path);

    // next anchor
    AnchorPointItem * itemLast = new AnchorPointItem(this);
    itemLast->setAnchorPos(pos);
    m_AnchorPointItems.append(itemLast);

    updateBoundingRect();
}

// creating
void FreeDrawingItem::downWhenCreating(QPointF point)
{
    QPointF pos = point;
    m_AnchorPointItems.last()->setAnchorPos(point);

    // generate subPath
    {
        m_subPaths.last().lineTo(pos);

        QPainterPath path;
        path.moveTo(pos);
        m_subPaths.append(path);
    }
    // next anchor
    AnchorPointItem * itemLast = new AnchorPointItem(this);
    itemLast->setAnchorPos(pos);
    m_AnchorPointItems.append(itemLast);

    updateBoundingRect();
}

void FreeDrawingItem::moveWhenCreating(QPointF point)
{
    if(m_subPaths.count())
    {
        QPainterPath path;
        int size = m_AnchorPointItems.count();
        path.moveTo(m_AnchorPointItems.at(size-2)->pos());
        path.lineTo(point);
        m_subPaths.last() = path;

        m_AnchorPointItems.last()->setAnchorPos(point);
    }

    updateBoundingRect();
}

void FreeDrawingItem::upWhenCreating(QPointF point)
{
    updateBoundingRect();
}

// end creating
void FreeDrawingItem::endCreate()
{
    if(!m_subPaths.isEmpty())
    {
        m_subPaths.removeLast();
    }

    if(!m_AnchorPointItems.isEmpty())
    {
//        qDebug()<<m_AnchorPointItems.count();
        AnchorPointItem * ptr = m_AnchorPointItems.takeLast();
        ptr->setParentItem(nullptr);
        ptr->deleteCtrl();
        delete ptr;
//        qDebug()<<m_AnchorPointItems.count();
    }

    updateBoundingRect();
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
