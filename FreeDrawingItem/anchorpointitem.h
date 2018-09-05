#ifndef ANCHORPOINTITEM_H
#define ANCHORPOINTITEM_H
#include "customitem.h"
#include <QPen>

class AnchorPointItem : public CustomItem
{
public:
    AnchorPointItem(QGraphicsItem *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

//    qreal getRadius();
private:
    QPen m_pen;
    qreal m_radius;
};

#endif // ANCHORPOINTITEM_H
