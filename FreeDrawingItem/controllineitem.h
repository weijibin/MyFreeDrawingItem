#ifndef CONTROLLINEITEM_H
#define CONTROLLINEITEM_H
#include "customitem.h"
#include <QPainterPath>
#include <QPen>

class ControlLineItem : public CustomItem
{
public:
    ControlLineItem(QGraphicsItem *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    void setLineInfo(const QPointF &start, const QPointF &end);
private:
    QPointF m_startPtn;
    QPointF m_endPtn;
    QPainterPath m_path;

    QPen m_pen;
};

#endif // CONTROLLINEITEM_H
