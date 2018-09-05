#include "anchorpointitem.h"
#include <QPainter>
#include <QPen>

AnchorPointItem::AnchorPointItem(QGraphicsItem *parent)
    : m_preCtrlPtnItem(*(new ControlPointItem)),m_postCtrlPtnItem(*(new ControlPointItem))
    , m_preLineItem(*(new ControlLineItem)),m_postLineItem(*(new ControlLineItem))
{
    m_radius = 4;
    this->setBoundingBox(QRectF(-1*m_radius,-1*m_radius,2*m_radius,2*m_radius));

    m_postLineItem.setParentItem(parent);
    m_preLineItem.setParentItem(parent);
    m_preCtrlPtnItem.setParentItem(parent);
    m_postCtrlPtnItem.setParentItem(parent);

    this->setParentItem(parent);
}

AnchorPointItem::~AnchorPointItem()
{

}

void AnchorPointItem::deleteCtrl()
{
    delete &m_preCtrlPtnItem;
    delete &m_preLineItem;
    delete &m_postCtrlPtnItem;
    delete &m_postLineItem;
}

void AnchorPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(Qt::darkMagenta));
    painter->drawEllipse(this->getBoundingBox());
    painter->restore();
}

void AnchorPointItem::setAnchorPos(QPointF pos)
{
    m_info.anchorPoint = pos;
    updatePropertyByInfo();
}

void AnchorPointItem::setPointInfo( const AnchorPointInfo &info)
{
    m_info = info;
    updatePropertyByInfo();
}

void AnchorPointItem::updatePropertyByInfo()
{
    this->setPos(m_info.anchorPoint);

    QPointF pos = m_info.anchorPoint;
    QPointF prePos = pos + QPointF(-30,-30);
    QPointF postPos = pos + QPointF(30,30);

    m_preCtrlPtnItem.setPos(prePos);
    m_postCtrlPtnItem.setPos(postPos);

    m_preLineItem.setLineInfo(pos,prePos);
    m_postLineItem.setLineInfo(pos,postPos);

//    if(m_info.pre_CtrlPoint == QPointF(-10000,-10000))
//    {
//        m_preCtrlPtnItem.setVisible(false);
//        m_preLineItem.setVisible(false);
//    }
//    else
    {
        m_preCtrlPtnItem.setVisible(true);
        m_preLineItem.setVisible(true);
    }

//    if(m_info.post_CtrlPoint == QPointF(-10000,-10000))
//    {
//        m_postCtrlPtnItem.setVisible(false);
//        m_postLineItem.setVisible(false);
//    }
//    else
    {
        m_postCtrlPtnItem.setVisible(true);
        m_postLineItem.setVisible(true);
    }

}
