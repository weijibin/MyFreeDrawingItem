#include "anchorpointitem.h"
#include <QPainter>
#include <QPen>
#include <QCursor>

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

    setCursor(QCursor(Qt::OpenHandCursor));

    setAcceptHoverEvents(true);
}

AnchorPointItem::~AnchorPointItem()
{

}

void AnchorPointItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void AnchorPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void AnchorPointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
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

void AnchorPointItem::setCtrlVisible(bool visible)
{
    m_isCtrlVisible = visible;

    m_preCtrlPtnItem.setVisible(visible);
    m_preLineItem.setVisible(visible);
    m_postCtrlPtnItem.setVisible(visible);
    m_postLineItem.setVisible(visible);
}

void AnchorPointItem::updatePropertyByInfo()
{
    this->setPos(m_info.anchorPoint);

    QPointF pos = m_info.anchorPoint;
    QPointF prePos = m_info.pre_CtrlPoint;
    QPointF postPos = m_info.post_CtrlPoint;

    m_preCtrlPtnItem.setPos(prePos);
    m_postCtrlPtnItem.setPos(postPos);

    m_preLineItem.setLineInfo(pos,prePos);
    m_postLineItem.setLineInfo(pos,postPos);

    if(m_info.pre_CtrlPoint == QPointF(-10000,-10000) || m_isCtrlVisible==false)
    {
        m_preCtrlPtnItem.setVisible(false);
        m_preLineItem.setVisible(false);
    }
    else
    {
        m_preCtrlPtnItem.setVisible(true);
        m_preLineItem.setVisible(true);
    }

    if(m_info.post_CtrlPoint == QPointF(-10000,-10000) || m_isCtrlVisible==false)
    {
        m_postCtrlPtnItem.setVisible(false);
        m_postLineItem.setVisible(false);
    }
    else
    {
        m_postCtrlPtnItem.setVisible(true);
        m_postLineItem.setVisible(true);
    }

}
