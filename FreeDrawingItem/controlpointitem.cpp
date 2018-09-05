#include "controlpointitem.h"
#include <QPainter>

ControlPointItem::ControlPointItem(QGraphicsItem *parent) : CustomItem(parent)
{
    m_radius = 4;
    this->setBoundingBox(QRectF(-1*m_radius,-1*m_radius,2*m_radius,2*m_radius));
}

void ControlPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(Qt::darkCyan));
    painter->drawEllipse(this->getBoundingBox());
    painter->restore();
}
