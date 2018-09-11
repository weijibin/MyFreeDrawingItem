#include "controlpointitem.h"
#include <QPainter>
#include <QCursor>
#include "anchorpointinfo.h"
#include "anchorpointitem.h"


ControlPointItem::ControlPointItem(QGraphicsItem *parent) : CustomItem(parent)
{
    m_radius = 4;
    this->setBoundingBox(QRectF(-1*m_radius,-1*m_radius,2*m_radius,2*m_radius));

    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void ControlPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(Qt::darkCyan));
    painter->drawEllipse(this->getBoundingBox());
    painter->restore();
}

void ControlPointItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    if(m_pointItem)
    {
        if(m_pointItem->getPointInfo().state == 1)
        {
            event->accept();
        }
    }

}

void ControlPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

    if(m_pointItem)
    {
        AnchorPointInfo info = m_pointItem->getPointInfo();
        if(info.state ==1)
        {
            QPointF nPtn = event->scenePos();
            setPos(nPtn);
            m_pointItem->updateInfoByPos(m_type);
        }
    }
}

void ControlPointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
