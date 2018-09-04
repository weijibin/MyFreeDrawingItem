#ifndef CONTROLLINEITEM_H
#define CONTROLLINEITEM_H
#include "customitem.h"

class ControlLineItem : public CustomItem
{
public:
    ControlLineItem(QGraphicsItem *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
};

#endif // CONTROLLINEITEM_H
