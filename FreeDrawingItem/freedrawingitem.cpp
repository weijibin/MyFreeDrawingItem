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
//    QRectF rect = childrenBoundingRect();
//    return rect;
//    qDebug()<<childrenBoundingRect();
    return m_boundingRect;
}

void FreeDrawingItem::updateBoundingRect()
{
    prepareGeometryChange();

    m_boundingRect = m_subPaths.first().controlPointRect();

    foreach (QPainterPath path, m_subPaths)
    {
        m_boundingRect = m_boundingRect.united(path.controlPointRect());
    }

//    m_boundingRect = childrenBoundingRect();
}

void FreeDrawingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::red);
    painter->drawRect(boundingRect());
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
    item->setFreeDrawingItem(this);

    item->setCtrlVisible(false);   // 隐藏控制点

    m_AnchorPointItems.append(item);


    //next sub Path
    QPainterPath path;
    path.moveTo(pos);
    m_subPaths.append(path);

    // next anchor
    AnchorPointItem * itemLast = new AnchorPointItem(this);
    itemLast->setAnchorPos(pos);
    itemLast->setFreeDrawingItem(this);

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
    itemLast->setFreeDrawingItem(this);

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

            {
                info.isSymmetrical = true;
            }

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

        m_AnchorPointItems.last()->setCtrlVisible(false); //隐藏最后Anchor的控制点
    }

    updateBoundingRect();
    synchronizeAnchorInfo(); // 创建完成后同步 锚点信息

    // hide control points
//    foreach (AnchorPointItem *item, m_AnchorPointItems)
//    {
//        item->setCtrlVisible(false);
//    }

    // 创建完成后 是编辑状态
    foreach (AnchorPointItem *item, m_AnchorPointItems)
    {
        item->setState(1);
    }
}

void FreeDrawingItem::synchronizeAnchorInfo()
{
    AnchorPointInfo curInfo,nextInfo;
    int count = m_AnchorPointItems.size();
    for(int i =  0; i < count-1; i++)
    {
        curInfo = m_AnchorPointItems.at(i)->getPointInfo();
        nextInfo = m_AnchorPointItems.at(i+1)->getPointInfo();

        if(curInfo.post_CtrlPoint == QPointF(-10000,-10000) && nextInfo.pre_CtrlPoint != QPointF(-10000,-10000))
        {
            curInfo.post_CtrlPoint = nextInfo.pre_CtrlPoint;
            {
                curInfo.post_Relation = true;
                nextInfo.pre_Relation = true;
            }
        }

        if(nextInfo.pre_CtrlPoint == QPointF(-10000,-10000) && curInfo.post_CtrlPoint != QPointF(-10000,-10000))
        {
            nextInfo.pre_CtrlPoint = curInfo.post_CtrlPoint;
            {
                curInfo.post_Relation = true;
                nextInfo.pre_Relation = true;
            }
        }

        m_AnchorPointItems.at(i)->setPointInfo(curInfo);
        m_AnchorPointItems.at(i+1)->setPointInfo(nextInfo);
    }

    // 设置最后Anchor的数据
    curInfo = m_AnchorPointItems.at(count-1)->getPointInfo();
    curInfo.post_CtrlPoint = QPointF(-10000,-10000);
    m_AnchorPointItems.at(count-1)->setPointInfo(curInfo);
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

QPainterPath FreeDrawingItem::generatePathByInfo(const AnchorPointInfo &first, const AnchorPointInfo &second)
{
    QPainterPath path;
    path.moveTo(first.anchorPoint);

    if( first.post_Relation==false && first.post_CtrlPoint == QPointF(-10000,-10000))
    {
        path.lineTo(second.anchorPoint);
    }
    else
    {
        if(first.post_Relation)
        {
            path.quadTo(first.post_CtrlPoint, second.anchorPoint);
        }
        else
        {
             path.cubicTo(first.post_CtrlPoint,second.pre_CtrlPoint,second.anchorPoint);
        }
    }

    return path;
}

void FreeDrawingItem::changePathByItem(AnchorPointItem *item)
{
    int index = m_AnchorPointItems.indexOf(item);
    int count = m_AnchorPointItems.count();

    qDebug()<< "FreeDrawingItem::changePathByItem";
    qDebug()<< index << count;

    if(index == 0)  // begin
    {
         AnchorPointInfo curInfo = m_AnchorPointItems.at(index)->getPointInfo();
         AnchorPointInfo postInfo = m_AnchorPointItems.at(index+1)->getPointInfo();

         QPainterPath path = generatePathByInfo(curInfo,postInfo);
         m_subPaths[index] = path;

         if(curInfo.post_Relation)  // update relational anchor point
         {
             postInfo.isSymmetrical = false;  //设置对称性，对称性被破坏

             postInfo.pre_CtrlPoint = curInfo.post_CtrlPoint;
             m_AnchorPointItems.at(index+1)->setPointInfo(postInfo,false);
         }
    }
    else if(index == count -1)  // end
    {
        AnchorPointInfo preInfo = m_AnchorPointItems.at(index-1)->getPointInfo();
        AnchorPointInfo curInfo = m_AnchorPointItems.at(index)->getPointInfo();

        QPainterPath path = generatePathByInfo(preInfo,curInfo);
        m_subPaths[index-1] = path;

        if(curInfo.pre_Relation)  // update relational anchor point
        {
            preInfo.isSymmetrical = false;

            preInfo.post_CtrlPoint = curInfo.pre_CtrlPoint;
            m_AnchorPointItems.at(index-1)->setPointInfo(preInfo,false);
        }
    }
    else // middle
    {
        AnchorPointInfo preInfo = m_AnchorPointItems.at(index-1)->getPointInfo();
        AnchorPointInfo curInfo = m_AnchorPointItems.at(index)->getPointInfo();
        AnchorPointInfo postInfo = m_AnchorPointItems.at(index+1)->getPointInfo();

        QPainterPath path1 = generatePathByInfo(preInfo,curInfo);
        m_subPaths[index-1] = path1;

        QPainterPath path2 = generatePathByInfo(curInfo,postInfo);
        m_subPaths[index] = path2;

         // update relational anchor point
        if(curInfo.pre_Relation)
        {
            preInfo.isSymmetrical = false;

            preInfo.post_CtrlPoint = curInfo.pre_CtrlPoint;
            m_AnchorPointItems.at(index-1)->setPointInfo(preInfo,false);
        }
        if(curInfo.post_Relation)
        {
            postInfo.isSymmetrical = false;

            postInfo.pre_CtrlPoint = curInfo.post_CtrlPoint;
            m_AnchorPointItems.at(index+1)->setPointInfo(postInfo,false);
        }
    }
    updateBoundingRect();
}
