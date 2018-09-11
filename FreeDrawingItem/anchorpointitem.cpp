#include "anchorpointitem.h"
#include "freedrawingitem.h"
#include <QPainter>
#include <QPen>
#include <QCursor>
#include <QPointF>

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

    m_preCtrlPtnItem.setPointItem(this);
    m_preCtrlPtnItem.setPosType("preCtrl");

    m_postCtrlPtnItem.setPointItem(this);
    m_postCtrlPtnItem.setPosType("postCtrl");

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

    if(m_info.state == 1)
    {
        event->accept();
    }
}

void AnchorPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if(m_info.state == 1)
    {
        QPointF nPtn = event->scenePos();

        QPointF offset = nPtn - m_info.anchorPoint;

        if(m_info.post_CtrlPoint != QPointF(-10000,-10000))
        {
            m_info.post_CtrlPoint += offset;
        }
        if(m_info.pre_CtrlPoint != QPointF(-10000,-10000))
        {
            m_info.pre_CtrlPoint += offset;
        }

        m_info.anchorPoint =nPtn;
        updatePropertyByInfo();
    }
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

void AnchorPointItem::setPointInfo( const AnchorPointInfo &info , bool needUpdate)
{
    m_info = info;
    if(needUpdate)
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

void AnchorPointItem::setState(int state)
{
    m_info.state = state;
}

void AnchorPointItem::setFreeDrawingItem(FreeDrawingItem *item)
{
    m_DrawingItem = item;
}

void AnchorPointItem::updateInfoByPos(const QString &type)
{

    QPointF pos = m_info.anchorPoint;
    QPointF prePos = m_preCtrlPtnItem.pos();
    QPointF postPos = m_postCtrlPtnItem.pos();

    if(m_info.isSymmetrical)  // 对称性处理
    {
        if(type == "preCtrl")
        {
            QPointF offset = pos-prePos;
            postPos = pos+offset;
            m_postCtrlPtnItem.setPos(postPos);
        }
        else
        {
            QPointF offset = pos-postPos;
            prePos = pos+offset;
            m_preCtrlPtnItem.setPos(prePos);
        }
    }

    m_info.pre_CtrlPoint = prePos;
    m_info.post_CtrlPoint = postPos;


    m_preLineItem.setLineInfo(pos,prePos);
    m_postLineItem.setLineInfo(pos,postPos);

    if(m_DrawingItem && m_info.state == 1)
    {
        m_DrawingItem->changePathByItem(this);
    }
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

//        m_preCtrlPtnItem.setPos(pos);
//        m_preLineItem.setLineInfo(pos,pos);
    }
    else
    {
        m_preCtrlPtnItem.setVisible(true);
        m_preLineItem.setVisible(true);

//        m_preCtrlPtnItem.setPos(prePos);
//        m_preLineItem.setLineInfo(pos,prePos);
    }

    if(m_info.post_CtrlPoint == QPointF(-10000,-10000) || m_isCtrlVisible==false)
    {
        m_postCtrlPtnItem.setVisible(false);
        m_postLineItem.setVisible(false);

//        m_postCtrlPtnItem.setPos(pos);
//        m_postLineItem.setLineInfo(pos,pos);
    }
    else
    {
        m_postCtrlPtnItem.setVisible(true);
        m_postLineItem.setVisible(true);

//        m_postCtrlPtnItem.setPos(postPos);
//        m_postLineItem.setLineInfo(pos,postPos);
    }

    if(m_DrawingItem && m_info.state == 1)
    {
        m_DrawingItem->changePathByItem(this);
    }

}
