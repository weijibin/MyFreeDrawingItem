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

    m_isPressed = true;
    m_downPoint = point;

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

    if(m_isPressed)
    {
        if(m_subPaths.count())
        {
            int size = m_AnchorPointItems.count();

            int pathCount = m_subPaths.count();

            AnchorPointInfo preInfo = m_AnchorPointItems.at(size-3)->getPointInfo();

            AnchorPointInfo info;
            info.anchorPoint = m_downPoint;
            info.post_CtrlPoint = point;

            QPointF  offset = m_downPoint - point;
            info.pre_CtrlPoint = m_downPoint + offset;

            m_AnchorPointItems.at(size-2)->setPointInfo(info);

            if( qAbs(preInfo.post_CtrlPoint.x() +10000) < 1)  // 二阶贝塞尔
            {
                QPainterPath path;
                path.moveTo(m_AnchorPointItems.at(size-3)->pos());
                path.quadTo(info.pre_CtrlPoint,info.anchorPoint);

//                m_subPaths.last() = path;
                m_subPaths[pathCount-2] = path;
            }
            else                    //三阶贝塞尔
            {
                QPainterPath path;
                path.moveTo(m_AnchorPointItems.at(size-3)->pos());
                path.cubicTo(preInfo.post_CtrlPoint,info.pre_CtrlPoint,info.anchorPoint);

//                m_subPaths.last() = path;
                 m_subPaths[pathCount-2] = path;
            }
        }
    }
    else
    {
        if(m_subPaths.count())
        {
            int size = m_AnchorPointItems.count();
            AnchorPointInfo preInfo = m_AnchorPointItems.at(size-2)->getPointInfo();
            if( qAbs(preInfo.post_CtrlPoint.x() +10000) < 1)  // line
            {
                QPainterPath path;
                path.moveTo(preInfo.anchorPoint);
                path.lineTo(point);
                m_subPaths.last() = path;
            }
            else                    //quad
            {
                QPainterPath path;
                path.moveTo(preInfo.anchorPoint);
                path.quadTo(preInfo.post_CtrlPoint,point);
                m_subPaths.last() = path;
            }
            m_AnchorPointItems.last()->setAnchorPos(point);
        }
    }

    updateBoundingRect();
}

void FreeDrawingItem::upWhenCreating(QPointF point)
{
    m_isPressed = false;
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
