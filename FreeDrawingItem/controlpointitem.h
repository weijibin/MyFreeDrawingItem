#ifndef CONTROLPOINTITEM_H
#define CONTROLPOINTITEM_H
#include "customitem.h"

class ControlPointItem : public CustomItem
{
public:
    ControlPointItem(QGraphicsItem *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
};

#endif // CONTROLPOINTITEM_H
