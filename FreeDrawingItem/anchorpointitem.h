#ifndef ANCHORPOINTITEM_H
#define ANCHORPOINTITEM_H
#include "customitem.h"

class AnchorPointItem : public CustomItem
{
public:
    AnchorPointItem(QGraphicsItem *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
};

#endif // ANCHORPOINTITEM_H
