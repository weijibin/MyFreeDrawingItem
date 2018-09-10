#include "controllineitem.h"
#include <QPainter>
#include <QDebug>

ControlLineItem::ControlLineItem(QGraphicsItem *parent) : CustomItem(parent)
{
    m_pen.setColor(Qt::gray);
    m_pen.setStyle(Qt::DotLine);
    m_pen.setWidth(2);
}

ControlLineItem::~ControlLineItem()
{
    qDebug()<<"delete ControlLineItem";
}

void ControlLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    painter->drawPath(m_path);
    painter->restore();
}

void ControlLineItem::setLineInfo(const QPointF &start, const QPointF &end)
{
    m_startPtn = start;
    m_endPtn = end;

    m_path.swap(QPainterPath());
    m_path.moveTo(start);
    m_path.lineTo(end);

    prepareGeometryChange();
    this->setBoundingBox(m_path.boundingRect());
}
